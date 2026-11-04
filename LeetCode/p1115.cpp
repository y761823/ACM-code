class FooBar {
private:
    int n;
    std::atomic_bool pfoo {true};

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            while (!pfoo.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            pfoo.store(false, std::memory_order_release);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            while (pfoo.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            pfoo.store(true, std::memory_order_release);
        }
    }
};
