# Accessing Private Members in C++

This repository presents a standard-compliant technique for accessing private class members from outside the class without causing undefined behavior.

## Background

I recently came across this approach when I discovered the project: [martong/access_private](https://github.com/martong/access_private). After some research, I found that this technique has been around for quite some time - the earliest mention I found dates back to a 2010 blog post titled [Access to private members. That's easy!](https://bloglitb.blogspot.com/2010/07/access-to-private-members-thats-easy.html).

This technique leverages a specific rule in the C++ standard that allows private types to be used in template arguments in explicit specializations and instantiations. According to the [C++23 standard](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf):

>The usual access checking rules do not apply to names in a declaration of an explicit instantiation or explicit specialization, with the exception of names appearing in a function body, default argument, base-clause, member-specification, enumerator-list, or static data member or variable template initializer.
>
>[Note 1: In particular, the template arguments and names used in the function declarator (including parameter types, return types, and exception specifications) can be private types or objects that would normally not be accessible. - end note]

However in 2015, [CWG Issue #2118](https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2118) was raised, questioning whether this approach should be considered ill-formed:

>Defining a friend function in a template, then referencing that function later provides a means of capturing and retrieving metaprogramming state. This technique is arcane and should be made ill-formed.

Recently, a new adaptations of this technique has emerged, leveraging changes in the C++20 standard to eliminate the need for capturing metaprogramming state. This approach can be found in the blog post [A Foliage of Folly](https://dfrib.github.io/a-foliage-of-folly/).

## Use Cases

This approach can be useful for testing scenarios where modifying the original class is not desirable — either because it belongs to a third-party software or because altering it would require significant changes. It can also be useful for modifying or extending features in third-party libraries, by providing access to members that do not have existing accessors.
