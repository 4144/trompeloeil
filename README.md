## *Trompeloeil*

![trompeloeil logo](trompeloeil-logo.png)  

> *trompe l'oeil* noun    (Concise Encyclopedia)  
> Style of representation in which a painted object is intended
> to deceive the viewer into believing it is the object itself...

What is it?
-----------

A header only mocking framework for C++14.

**NOTE! These are still early days. Bugs will be found, and important features
are missing. Code breaking changes are no longer expected, but may still
occurr.**

Example usage
-------------

```Cpp
#include "trompeloeil.hpp"

class I
{
public:
  I(const char*);
  virtual bool foo(int, std::string& s) = 0;
  virtual bool bar(int) = 0;
  virtual bool bar(std::string) = 0;
};

class CUT
{
public:
  CUT(I* i);
  std::string work(int n);
};

class MI : public trompeloeil::mocked_class<I>
{
public:
  using mocked_class::mocked_class;
  MOCK(foo, (int, std::string&));
  MOCK(bar, (int));
  MOCK(bar, (std::string));
};

TEST(work_returns_the_string_obtained_from_I_foo)
{
  using trompeloeil::_; // wildcard for matching any value

  MI mock_i("word");
  CUT out(&mock_i);

  DEATHWATCH(mock_i);

  {
    trompeloeil::sequence seq;
    REQUIRE_CALL(mock_i, foo(3, _))
    .WITH(_2 == "")
    .TIMES(1)
    .IN_SEQUENCE(seq)
    .SIDE_EFFECT(_2 = "cat")
    .RETURN(true);

    REQUIRE_CALL(mock_i, bar(ANY(int)))
    .RETURN(false);

    auto s = out.work(3);

    ASSERT(s == "cat");
  }

  REQUIRE_DESTRUCTION(mock_i);
}
```

Limitations (TODO-list)
-----------------------
- Private methods cannot be mocked
- Mock function parameter types must not include commas (i.e. must not be of
  template types with more than one template parameter.)
  * use a typedef as a simple work-around
- Function templates cannot be mocked
- Reporting needs more work
- Tracing
- WAY too many macros...  
  * uses empty __VA_ARGS__, which is illegal (although harmless)
    - With `GCC`, don't use `-pedantic` on the command line
    - With `clang`, add `-Wno-gnu-zero-variadic-macro-argument` to the command line


How to use
----------
The example above shows most currently supported functionality.

## Types & Templates

**`trompeloeil::sequence`**  
Type of sequence objects, used to impose an order of matching invocations of
**`REQUIRE_CALL`** instances. Several sequence objects can be used to denote
parallel sequences, and several sequence objects can be joined in one
**`REQUIRE_CALL`**.

**`trompeloeil::mocked_class&lt;T&gt;`**  
All mock objects inherit from an instantiation of **`mocked_class&lt;&gt;`**
of the type they mock. The template provides the necessary information for
the rest of the machinery to work. Template instantiations inherits all
constructors of `&lt;T&gt;`.

**`trompeloeil::wildcard`**  
The type of the wildcard object **`trompeloeil::_**`. You typically never see
the type itself.

## Macros

If the generic macro names conflicts with others in your sources, define the
macro **`TROMPELOEIL_LONG_MACROS`** before inclusion of `trompeloeil.hpp`. It
prefixes all macros listed below with **`TROMPELOEIL_`**.

**`ANY`(** *type* **)**  
Typed wildcard to disambiguate overloaded functions on type when the exact
value is unimportant.

**`AT_LEAST`**( *number* **)**  
Used in **`.TIMES`()** to set the range *number*..infinity. *number* must be
`constexpr`.

**`AT_MOST`**( *number* **)**  
Used in **`.TIMES`()** to set the range 0..*number*. *number* must be
`constexpr`.

**`MOCK`(** *method_name*, *parameter_list* **)**  
Make a mock implementation of the method named *method_name*. *method_name*
must be virtual, and may currently not be overloded with several signatures.

**`MOCK_CONST`(** *method_name*, *parameter_list* **)**  
Same as **`MOCK`(** *method_name*, *parameter_list* **)** for `const` methods.

**`REQUIRE_CALL`(** *mock_object*, *method_name*(*parameter_list*)**)**  
Set up an expectaion that the method *method_name* is called on the object
*mock_object*. The parameter list may include exact match values, or the
wildcard `trompeloeil::_`. The expectation has scope lifetime and must be
met by the time the scope ends. When there are several expectations active on
the same object and method, they are tried in the reversed order they were
defined, i.e. last defined is tried first, until a match is found. This allows
you to specify a wide default early, and narrow specializations in short
scopes.

**`NAMED_REQUIRE_CALL`(** *mock_object*, *method_name*(*parameter_list*)**)**
Same as **`REQUIRE_CALL`**, except it instantiates a
*std::unique_ptr&lt;trompeloeil::expectation&gt;* which you can bind to a
variable.

**`DEATHWATCH`(** *mock_object* **)**  
Set up a deathwatch for *mock_object*, meaning its destruction is monitored.
It is an error if *mock_object* is destroyed before a
**`REQUIRE_DESTRUCTION`()** is active.

**`REQUIRE_DESTRUCTION`(** *mock_object* **)**  
Makes it legal for *mock_object* to be destroyed when a **`DEATHWATCH`**() is
active for it. It is an error if *mock_object* is still alive at end of scope.

**`NAMED_REQUIRE_DESTRUCTION`(** *mock_object* **)**  
Same as **`REQUIRE_DESTRUCTION`**, except it instantiates a
*std::unique_ptr&lt;trompeloeil::lifetime_monitor&gt;* which you can bind to a
variable.

**`.WITH`(** *expr* **)**  
Add further conditions for a **`REQUIRE_CALL`**, typically used when the
wildcard `trompeloeil::_` has been used. *expr* can refer to parameters in the
call with their positional names `_1`, `_2`, etc. Even if the
function signature has parameter as non-`const` references, they are
immutable in this context. Several **`.WITH`** clauses can be added to a single
**`REQUIRE_CALL`**

**`.SIDE_EFFECT`(** *expr* **)**  
Code to cause side effects. *expr* is only evaluated when all **`.WITH`**
clauses are matched. *expr* may refer to parameters in the call with their
positional names `_1`, `_2`, etc. This code may alter out-parameters.
Several **`.SIDE_EFFECT`** clauses can be added to a single **`REQUIRE_CALL`**

**`.RETURN`(** *expr* **)**  
Set the return value after having evaluated every **`.SIDE_EFFECT`** . For `void`
functions **`.RETURN`** is illegal. For non-`void` functions **`.RETURN`** is
required exactly once. *expr* may refer to parameters in the call with their
positional names `_1`, `_2`, etc. This code may alter out-parameters. If you
need to return an lvalue reference, use `std::ref()`.

**`.TIMES`(** *limit* **)**  
Set the number of times the call is allowed. *limits* must be `constexpr`.
*limits* may be one number specifying an exact amount, or two numbers
specifying a range. A lower limit of `0` means the call is not required.
By default a **`REQUIRE_CALL`** is expected to be tripped exactly once.
**`.TIMES`** may only be used once for a **`REQUIRE_CALL`**

**`.IN_SEQUENCE`(** *seq...* **)**  
Where *seq...* is one or more instances of `trompeloeil::sequence`. Impose an
order in which **`.REQUIRE_CALL`** must match. Several sequences can be parallel
and interleaved. A sequence for a **`.REQUIRE_CALL`** is no longer monitored
once the lower limit from **`.TIMES`** is reached.

**`ALLOW_CALL`(** *mock_object*, *method_name*(*parameter_list*)**)**  
Same as **`REQUIRE_CALL`**().**`TIMES`(** 0, infinity **)**. Matches any
number of times, but is not required to match. (_actually the limit is
0..~0ULL, but that is for all practical purposes "infinity"_)

**`NAMED_ALLOW_CALL`(** *mock_object*, *method_name*(*parameter_list*)**)**  
Same as **`NAMED_REQUIRE_CALL`**().**`TIMES`(** 0, infinity **)**.
Matches any number of times, but is not required to match. (_actually the limit
is 0..~0ULL, but that is for all practical purposes "infinity"_)

**`FORBID_CALL`(** *mock_object*, *method_name*(*parameter_list*)**)**  
Same as **`REQUIRE_CALL`**().**`TIMES`(** 0 **)**, making any matching call
an error.

**`NAMED_FORBID_CALL`(** *mock_object*, *method_name*(*parameter_list*)**)**  
Same as **`NAMED_REQUIRE_CALL`**().**`TIMES`(** 0 **)**, making any matching
call an error.

## Printing values

By default *`trompeloeil`* prints any values in violation reports using
the defined output stream `operator<<` for the type. If none is available,
the objects memory region is printed as a hex-dump.

Should you want to provide a special print function for use in tests,
define a function `void print(std::ostream&, const TYPE&)` in namespace
`trompeloeil` for your type.

## Report to test frameworks

By default *`trompeloeil`* reports all violations as exceptions. This
works with most test frameworks, but since the error of not having matched
a **`REQUIRE_CALL`** is not discovered until the match object goes out of
scope and is destroyed, this error will call *`std::terminate()`*, which
is typically not what you want.

There is a function  
```Cpp
trompeloeil::set_reporter(std::function<void(trompeloeil::severity,
                                             const std::string& location
                                             const std::string& msg)>)
```
which can be used to control the reporting. `trompeloeil::severity` is an enum
with the values `fatal` and `nonfatal`. Severity is `nonfatal` when called
from the destructor of a **`REQUIRE_CALL`** object due to unfulfilled
expectations. Some examples are:

### catch
```Cpp
  trompeloeil::set_reporter([](::trompeloeil::severity s,
                               const std::string& loc,
                               const std::string& msg)
    {
      auto m = loc + "\n" = msg;
      if (s == ::trompeloeil::severity::fatal)
        {
          FAIL(m);
        }
      CHECK(m == "");
    });
```

### crpcut
```Cpp
  trompeloeil::set_reporter([](::trompeloeil::severity,
                               const std::string& loc,
                               const std::string& msg)
    {
      auto location = loc.empty()
        ? ::crpcut::crpcut_test_monitor::current_test()->get_location()
        : ::crpcut::datatypes::fixed_string{loc.c_str(), loc.length()};
      ::crpcut::comm::report(::crpcut::comm::exit_fail,
                             std::ostringstream(msg),
                             location);
    });
```
