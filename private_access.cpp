#include <iostream>


class A {
private:
    void print_x() { std::cout << x << std::endl; }

    int x;
};

/*
 * Tag type for accessing A::x. Each private member requires a unique tag because, if multiple members share the same type, the compiler cannot differentiate between them. For instance, comparing "int A::*" to another "int A::*" would be ambiguous.
 *
 * Each tag defines a nested "::type" representing the corresponding pointer-to-member type.
 * Additionally, each tag declares a unique overload of the "get" method that provides access to its corresponding private member.
 */
struct tag_x {
  using type = int A::*;
  
  // Calling get() is only valid if the "Access" class has been instantiated for this tag.
  friend type get(tag_x);
};

// Similar to tag_x, but designed for a private member function instead of a data member.
struct tag_print_x {
  using type = void(A::*)();

  friend type get(tag_print_x);
};

// This class defines a friend function that can be called via ADL using the tag type.
template<typename Tag, typename Tag::type mem_ptr>
struct Access {
  friend typename Tag::type get(Tag) {
    return mem_ptr;
  }
};

// Explicit instantiation; this is the only place where it is allowed to pass the address of a private member.
template struct Access<tag_x, &A::x>;
template struct Access<tag_print_x, &A::print_x>;

int main() {
  A a;
  a.*get(tag_x()) = 7;
  std::cout << a.*get(tag_x()) << std::endl;
  (a.*get(tag_print_x()))();
}
