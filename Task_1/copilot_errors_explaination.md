The exit code `-1073740940 (0xC0000374)` is a status code indicating a heap corruption. This usually happens when you're trying to delete a pointer that has not been allocated with `new`, or you're trying to delete a pointer twice.

Looking at your `test()` function, there are two potential issues:

1. You're calling `delete ptrC;` but `ptrC` was not allocated with `new`. It's actually a pointer to `c1`, which is a stack-allocated object. Trying to `delete` a stack-allocated object leads to undefined behavior and can cause heap corruption.

2. You're calling `delete ptrB;` but then you're using `ptrB` again in the line `ptrC->method1(&c2);`. This is because `ptrC` is a pointer to `c1`, and `c1` is a copy of the object that `ptrB` pointed to. When you `delete ptrB`, you're deallocating the memory that `c1` (and therefore `ptrC`) is referring to. This leads to undefined behavior and can cause heap corruption.

Here's how you can modify your `test()` function to fix these issues:

```cpp
void test() {
    Child c1;
    Child c2 = c1;
    Base b1;
    Base* ptrB = new Child();
    ptrB->method1(c1);
    static_cast<Child *>(ptrB)->method2();
    c1.method2();
    Child *ptrC = &c1;
    ptrC->method1(&c2);
    delete ptrB;
}
```

In this modified version of `test()`, `ptrB` is allocated with `new` and then deleted, and `ptrC` is not deleted because it's not allocated with `new`. This should prevent the heap corruption error.
