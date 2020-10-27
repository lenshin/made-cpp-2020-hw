#include <iostream>


using namespace std;

struct Memory {
  Memory(char *ptr, size_t count, Memory *next = nullptr) : ptr(ptr), count(count), next(next) {}
  char *ptr;
  size_t count;
  Memory *next;
};

template<typename T>
class Chunk {
private:
  Memory *busy;

public:
  char *data;
  Chunk *next;
  explicit Chunk(Chunk *next = nullptr) : next(next) {
    data = new char[N * sizeof(T)];
  }
  ~Chunk() {
    Memory *temp = busy;
    while (temp != nullptr) {
      Memory *del = temp;
      temp = temp->next;
      delete del;
    }
    busy = nullptr;
    next = nullptr;
    delete[] data;
    data = nullptr;
  }

  char *get(size_t size) {
    if (busy != nullptr) {
      if (busy->ptr - data >= size) {
        busy->next = new Memory(data, size);
        return busy->next->ptr;
      }

      if (busy->next == nullptr)
        if (data + N - (busy->ptr + busy->count) >= size) {
          busy->next = new Memory(busy->ptr + busy->count, size);
          return busy->next->ptr;
        } else {
          return nullptr;
        }
      Memory *p1 = busy;
      Memory *p2 = busy->next;

      while (p2 != nullptr) {
        if (p2->ptr - (p1->ptr + p1->count) >= size) {
          p1->next = new Memory(p1->ptr + p1->count, size, p2);
          return p1->next->ptr;
        }
        p1 = p2;
        p2 = p2->next;
      }

      if (data + N - (p1->ptr + p1->count) >= size) {
        p1->next = new Memory(p1->ptr + p1->count, size);
        return p1->next->ptr;
      }

      return nullptr;
    } else {
      busy = new Memory(data, size, nullptr);
      return busy->ptr;
    }
  }

  bool del(T *ptr) {
    if (busy != nullptr) {
      if (busy->ptr == (char *) ptr) {
        Memory *del = busy;
        busy = busy->next;
        delete del;
        return true;
      }

      Memory *temp = busy;
      while (temp->next != nullptr)
        if (temp->next->ptr == (char *) ptr) {
          Memory *del = temp->next;
          temp->next = del->next;
          delete del;
          return true;
        }
    }
    return false;
  }

  static const size_t N = 100;
};

template<typename T>
class Allocator {
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = T*;
  using reference = T &;
  using const_reference = const T&;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  template<class U>
  struct rebind {
    using other = Allocator<U>;
  };

public:
  Allocator() {
    tail = nullptr;
    count = new size_t;
    *count = 0;
  }

  Allocator(const Allocator &copy) {
    tail = copy.tail;
    count = copy.count;
    (*count)++;
  }

  ~Allocator() {
    if (*count > 1)
      (*count)--;
    else {
      Chunk<T> *temp = tail;
      while (temp != nullptr) {
        Chunk<T> *del = temp;
        temp = temp->next;
        delete del;
      }
      tail = nullptr;
      delete[] count;
      count = nullptr;
    }
  }

  T *allocate(size_t size) {
    if (size <= Chunk<T>::N) {
      T *ptr = nullptr;
      tail = tail != nullptr ? tail : (new Chunk<T>);
      Chunk<T> *temp = tail;
      do {
        ptr = (T *) temp->get(size);
        temp = temp->next;
      } while (ptr == nullptr && temp != nullptr);

      if (temp == nullptr && ptr == nullptr) {
        tail = new Chunk<T>(tail);
        ptr = (T *) tail->get(size);
      }

      return ptr;
    }
    return nullptr;
  }

  void deallocate(T *ptr, size_t size) {
    if (tail != nullptr) {
      Chunk<T> *temp = tail;
      while (temp != nullptr && !temp->del(ptr))
        temp = temp->next;
    }
  }

  static size_t max_size() { return Chunk<T>::N; }

  Allocator &operator=(const Allocator &B) {
    this->~Allocator();
    tail = B.tail;
    (*B.count)++;
    count = B.count;
    return *this;
  }


  template<typename ...Args>
  void construct(T* ptr, const Args&&... args) {
    return new(ptr) T(args...);
  };

  void destroy(T *ptr) {
    ptr->~T();
  };

private:
  size_t *count;
  Chunk<T> *tail{};
};