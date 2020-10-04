#include <iostream>
#include <functional>

typedef std::function<int (int)> Op;



Op compose (size_t n, Op ops[]) {
    auto comp0 = [] (int x) -> int {
        return x;
    };

    auto comp1 = [] (Op fun) -> Op {
        return [=] (int x) {
            return fun(x);
        };
    };

    auto comp = [] (Op fun1, Op fun2) -> Op {
        return [=] (int x) {
            return fun1(fun2(x));
        };
    };

    if (n == 0) {
        return comp0;

    } else if (n == 1) {
        return comp1(ops[0]);

    } else {
        auto composed = comp(ops[0], ops[1]);
        for (size_t i = 2; i < n; ++ i) {
            composed = comp(composed, ops[i]);
        };
        return composed;
    }    
}


int main () {
    /// Simple tests:

    Op op1 =
        [] (int x) -> int {
            return x + 1;
        };

    auto op2 =
        [] (int p) -> Op {
            return [p] (int x) {
                return p * x;
            };
        };

    {
        Op ops[4] = {op1, op2(2), op1, op2(2)};
        if (compose(4, ops)(2) != 11) {
            std::cout << "FAILED AT TEST 1" << std::endl;
            return 0;
        }
    }

    {
        Op ops[8] = {op1, op2(2), op1, op1, op1, op2(2), op2(2), op1};
        if (compose(8, ops)(5) != 55) {
            std::cout << "FAILED AT TEST 2" << std::endl;
            return 0;
        }
    }

    {
        Op ops[1] = {op1};
        if (compose(1, ops)(3) != 4) {
            std::cout << "FAILED AT TEST 3" << std::endl;
            return 0;
        }
    }

    {
        Op ops[0] = {};
        if (compose(0, ops)(4) != 4) {
            std::cout << "FAILED AT TEST 4" << std::endl;
            return 0;
        }
    }

    {
        Op ops[4] = {op2(2), op2(3), op2(4), op2(5)};
        if (compose(4, ops)(1) != 120) {
            std::cout << "FAILED AT TEST 5" << std::endl;
            return 0;
        }
    }
}
