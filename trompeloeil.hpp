#ifndef TROMPELOEIL_HPP_
#define TROMPELOEIL_HPP_

// trompe l'oeil noun    (Concise Encyclopedia)
// Style of representation in which a painted object is intended
// to deceive the viewer into believing it is the object itself...


// Deficiencies and missing features
// * Mocking private methods is not supported
// * Mocking function templates is not supported
// * Reporting really needs working on
// * implement tracing
// * If a macro kills a kitten, this threatens extinction of all felines!
//   * With GCC, avoid -pedantic to avoid warnings about empty __VA_ARGS__
//   * Wth clang, add -Wno-gnu-zero-variadic-macro-argument to avoid
//     warnings about empty __VA_ARGS__

#if (!defined(__cplusplus) || __cplusplus <= 201103)
#error requires C++14 or higher
#endif

#include <utility>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <functional>
#include <memory>
#include <cassert>

#define TROMPELOEIL_APPLY(x,...) x(__VA_ARGS__)
#define TROMPELOEIL_CONCAT5(x, ...) TROMPELOEIL_CONCAT4(x ## __VA_ARGS__)
#define TROMPELOEIL_CONCAT4(x, ...) TROMPELOEIL_CONCAT3(x ## __VA_ARGS__)
#define TROMPELOEIL_CONCAT3(x, ...) TROMPELOEIL_CONCAT2(x ## __VA_ARGS__)
#define TROMPELOEIL_CONCAT2(x, ...) TROMPELOEIL_CONCAT1(x ## __VA_ARGS__)
#define TROMPELOEIL_CONCAT1(x) x


#define TROMPELOEIL_ARG16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15, ...) _15
#define TROMPELOEIL_HAS_COMMA(...) TROMPELOEIL_ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1,  1,  1,  0)

#define TROMPELOEIL_MAKE_COMMA(...) ,


#define TROMPELOEIL_ISEMPTY(...)                                                    \
  TROMPELOEIL_ISEMPTY_(                                                             \
           TROMPELOEIL_HAS_COMMA(__VA_ARGS__),                                      \
           TROMPELOEIL_HAS_COMMA(TROMPELOEIL_MAKE_COMMA __VA_ARGS__),                           \
           TROMPELOEIL_HAS_COMMA(__VA_ARGS__ (/*empty*/)),                          \
           TROMPELOEIL_HAS_COMMA(TROMPELOEIL_MAKE_COMMA __VA_ARGS__ ()))


#define TROMPELOEIL_ISEMPTY_(a,b,c,d) TROMPELOEIL_HAS_COMMA(TROMPELOEIL_CONCAT5(IS_EMPTY_CASE_,a,b,c,d))
#define IS_EMPTY_CASE_0001 ,

#define TROMPELOEIL_COUNT0(...) TROMPELOEIL_ARG16(__VA_ARGS__,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define TROMPELOEIL_COUNT1() 0
#define TROMPELOEIL_COUNT(...) TROMPELOEIL_APPLY(TROMPELOEIL_CONCAT2, TROMPELOEIL_COUNT,  TROMPELOEIL_ISEMPTY(__VA_ARGS__))(__VA_ARGS__)


#define TROMPELOEIL_PLIST15(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15)  \
  TROMPELOEIL_PLIST14(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14), \
  trompeloeil::c ## _type_catcher<void(P15)> p15

#define TROMPELOEIL_PLIST14(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14)  \
  TROMPELOEIL_PLIST13(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13), \
  trompeloeil::c ## _type_catcher<void(P14)> p14

#define TROMPELOEIL_PLIST13(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)  \
  TROMPELOEIL_PLIST12(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12), \
  trompeloeil::c ## _type_catcher<void(P13)> p13

#define TROMPELOEIL_PLIST12(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)  \
  TROMPELOEIL_PLIST11(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11), \
  trompeloeil::c ## _type_catcher<void(P12)> p12

#define TROMPELOEIL_PLIST11(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)  \
  TROMPELOEIL_PLIST10(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10), \
  trompeloeil::c ## _type_catcher<void(P11)> p11

#define TROMPELOEIL_PLIST10(c, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)  \
  TROMPELOEIL_PLIST9(c, P1, P2, P3, P4, P5, P6, P7, P8, P9), \
  trompeloeil::c ## _type_catcher<void(P10)> p10

#define TROMPELOEIL_PLIST9(c, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
  TROMPELOEIL_PLIST8(c, P1, P2, P3, P4, P5, P6, P7, P8), \
  trompeloeil::c ## _type_catcher<void(P9)> p9

#define TROMPELOEIL_PLIST8(c, P1, P2, P3, P4, P5, P6, P7, P8) \
  TROMPELOEIL_PLIST7(c, P1, P2, P3, P4, P5, P6, P7), \
  trompeloeil::c ## _type_catcher<void(P8)> p8

#define TROMPELOEIL_PLIST7(c, P1, P2, P3, P4, P5, P6, P7) \
  TROMPELOEIL_PLIST6(c, P1, P2, P3, P4, P5, P6), \
  trompeloeil::c ## _type_catcher<void(P7)> p7

#define TROMPELOEIL_PLIST6(c, P1, P2, P3, P4, P5, P6) \
  TROMPELOEIL_PLIST5(c, P1, P2, P3, P4, P5), \
  trompeloeil::c ## _type_catcher<void(P6)> p6

#define TROMPELOEIL_PLIST5(c, P1, P2, P3, P4, P5) \
  TROMPELOEIL_PLIST4(c, P1, P2, P3, P4), \
  trompeloeil::c ## _type_catcher<void(P5)> p5

#define TROMPELOEIL_PLIST4(c, P1, P2, P3, P4)  \
  TROMPELOEIL_PLIST3(c, P1, P2, P3), \
  trompeloeil::c ## _type_catcher<void(P4)> p4

#define TROMPELOEIL_PLIST3(c, P1, P2, P3) \
  TROMPELOEIL_PLIST2(c, P1, P2), \
  trompeloeil::c ## _type_catcher<void(P3)> p3

#define TROMPELOEIL_PLIST2(c, P1, P2) \
  TROMPELOEIL_PLIST1(c, P1), \
  trompeloeil::c ## _type_catcher<void(P2)> p2

#define TROMPELOEIL_PLIST1(c, P1) trompeloeil::c ## _type_catcher<void(P1)> p1
#define TROMPELOEIL_PLIST0(c, P0)

#define TROMPELOEIL_VLIST15(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15) \
  TROMPELOEIL_VLIST14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14),     \
  std::declval<trompeloeil::ref_type_catcher<void(P15)> >()

#define TROMPELOEIL_VLIST14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
  TROMPELOEIL_VLIST13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13),          \
  std::declval<trompeloeil::base_type_catcher<void(P14)> >()

#define TROMPELOEIL_VLIST13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13)     \
  TROMPELOEIL_VLIST12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12),               \
  std::declval<trompeloeil::ref_type_catcher<void(P13)> >()

#define TROMPELOEIL_VLIST12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12)          \
  TROMPELOEIL_VLIST11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11),                    \
  std::declval<trompeloeil::ref_type_catcher<void(P12)> >()

#define TROMPELOEIL_VLIST11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11)               \
  TROMPELOEIL_VLIST10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10),                          \
  std::declval<trompeloeil::ref_type_catcher<void(P11)> >()

#define TROMPELOEIL_VLIST10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)                    \
  TROMPELOEIL_VLIST9(P1, P2, P3, P4, P5, P6, P7, P8, P9),                              \
  std::declval<trompeloeil::ref_type_catcher<void(P10)> >()

#define TROMPELOEIL_VLIST9(P1, P2, P3, P4, P5, P6, P7, P8, P9)                         \
  TROMPELOEIL_VLIST8(P1, P2, P3, P4, P5, P6, P7, P8),                                  \
  std::declval<trompeloeil::ref_type_catcher<void(P9)> >()

#define TROMPELOEIL_VLIST8(P1, P2, P3, P4, P5, P6, P7, P8)                             \
  TROMPELOEIL_VLIST7(P1, P2, P3, P4, P5, P6, P7),                                   \
  std::declval<trompeloeil::ref_type_catcher<void(P8)> >()

#define TROMPELOEIL_VLIST7(P1, P2, P3, P4, P5, P6, P7)                            \
  TROMPELOEIL_VLIST6(P1, P2, P3, P4, P5, P6),                                        \
  std::declval<trompeloeil::ref_type_catcher<void(P7)> >()

#define TROMPELOEIL_VLIST6(P1, P2, P3, P4, P5, P6)             \
  TROMPELOEIL_VLIST5(P1, P2, P3, P4, P5),                                      \
  std::declval<trompeloeil::ref_type_catcher<void(P6)> >()

#define TROMPELOEIL_VLIST5(P1, P2, P3, P4, P5) \
  TROMPELOEIL_VLIST4(P1, P2, P3, P4), \
  std::declval<trompeloeil::ref_type_catcher<void(P5)> >()

#define TROMPELOEIL_VLIST4(P1, P2, P3, P4) \
  TROMPELOEIL_VLIST3(P1, P2, P3), \
  std::declval<trompeloeil::ref_type_catcher<void(P4)> >()

#define TROMPELOEIL_VLIST3(P1, P2, P3)                         \
  TROMPELOEIL_VLIST2(P1, P2),                                                  \
  std::declval<trompeloeil::ref_type_catcher<void(P3)> >()

#define TROMPELOEIL_VLIST2(P1, P2) \
  TROMPELOEIL_VLIST1(P1),          \
  std::declval<trompeloeil::ref_type_catcher<void(P2)> >()

#define TROMPELOEIL_VLIST1(P1) \
  std::declval<trompeloeil::ref_type_catcher<void(P1)> >()
#define TROMPELOEIL_VLIST0()

#define TROMPELOEIL_CONCAT_(x, y) x ## y
#define TROMPELOEIL_CONCAT(x, y) TROMPELOEIL_CONCAT_(x, y)
#define CONST_REF_TROMPELOEIL_PLIST(...) TROMPELOEIL_CONCAT(TROMPELOEIL_PLIST, TROMPELOEIL_COUNT(__VA_ARGS__)) (const_ref, __VA_ARGS__)
#define REF_TROMPELOEIL_PLIST(...) TROMPELOEIL_CONCAT(TROMPELOEIL_PLIST, TROMPELOEIL_COUNT(__VA_ARGS__)) (ref, __VA_ARGS__)
#define VERBATIM_TROMPELOEIL_PLIST(...) TROMPELOEIL_CONCAT(TROMPELOEIL_PLIST, TROMPELOEIL_COUNT(__VA_ARGS__)) (verbatim, __VA_ARGS__)
#define TROMPELOEIL_VLIST(...) TROMPELOEIL_CONCAT(TROMPELOEIL_VLIST, TROMPELOEIL_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define TROMPELOEIL_CLIST15(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15) \
  TROMPELOEIL_CLIST14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14), \
  static_cast<::trompeloeil::ref_type_catcher<void(P15)> >(p15)

#define TROMPELOEIL_CLIST14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
  TROMPELOEIL_CLIST13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13), \
  static_cast<::trompeloeil::ref_type_catcher<void(P14)> >(p14)

#define TROMPELOEIL_CLIST13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
  TROMPELOEIL_CLIST12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12),   \
  static_cast<::trompeloeil::ref_type_catcher<void(P13)> >(p13)

#define TROMPELOEIL_CLIST12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
  TROMPELOEIL_CLIST11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11),        \
  static_cast<::trompeloeil::ref_type_catcher<void(P12)> >(p12)

#define TROMPELOEIL_CLIST11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
  TROMPELOEIL_CLIST10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10),         \
  static_cast<::trompeloeil::ref_type_catcher<void(P11)> >(p11)

#define TROMPELOEIL_CLIST10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
  TROMPELOEIL_CLIST9(P1, P2, P3, P4, P5, P6, P7, P8, P9),            \
  static_cast<::trompeloeil::ref_type_catcher<void(P10)> >(p10)

#define TROMPELOEIL_CLIST9(P1, P2, P3, P4, P5, P6, P7, P8, P9)  \
  TROMPELOEIL_CLIST8(P1, P2, P3, P4, P5, P6, P7, P8),           \
  static_cast<::trompeloeil::ref_type_catcher<void(P9)> >(p9)

#define TROMPELOEIL_CLIST8(P1, P2, P3, P4, P5, P6, P7, P8)      \
  TROMPELOEIL_CLIST7(P1, P2, P3, P4, P5, P6, P7),               \
  static_cast<::trompeloeil::ref_type_catcher<void(P8)> >(p8)

#define TROMPELOEIL_CLIST7(P1, P2, P3, P4, P5, P6, P7)          \
  TROMPELOEIL_CLIST6(P1, P2, P3, P4, P5, P6),                   \
  static_cast<::trompeloeil::ref_type_catcher<void(P7)> >(p7)

#define TROMPELOEIL_CLIST6(P1, P2, P3, P4, P5, P6)              \
  TROMPELOEIL_CLIST5(P1, P2, P3, P4, P5),                       \
  static_cast<::trompeloeil::ref_type_catcher<void(P6)> >(p6)

#define TROMPELOEIL_CLIST5(P1, P2, P3, P4, P5)                  \
  TROMPELOEIL_CLIST4(P1, P2, P3, P4),                           \
  static_cast<::trompeloeil::ref_type_catcher<void(P5)> >(p5)

#define TROMPELOEIL_CLIST4(P1, P2, P3, P4)                      \
  TROMPELOEIL_CLIST3(P1, P2, P3),                               \
  static_cast<::trompeloeil::ref_type_catcher<void(P4)> >(p4)

#define TROMPELOEIL_CLIST3(P1, P2, P3)                          \
  TROMPELOEIL_CLIST2(P1, P2),                                   \
  static_cast<::trompeloeil::ref_type_catcher<void(P3)> >(p3)

#define TROMPELOEIL_CLIST2(P1, P2)                              \
  TROMPELOEIL_CLIST1(P1),                                       \
  static_cast<::trompeloeil::ref_type_catcher<void(P2)> >(p2)

#define TROMPELOEIL_CLIST1(P1) \
  static_cast<::trompeloeil::ref_type_catcher<void(P1)> >(p1)

#define TROMPELOEIL_CLIST0()
#define TROMPELOEIL_CLIST(...) ( TROMPELOEIL_CONCAT(TROMPELOEIL_CLIST, TROMPELOEIL_COUNT(__VA_ARGS__)) (__VA_ARGS__) )

#define TROMPELOEIL_INIT_WITH_STR15(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR14(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR14(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR13(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR13(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR12(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR12(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR11(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR11(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR10(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR10(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR9(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR9(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR8(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR8(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR7(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR7(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR6(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR6(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR5(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR5(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR4(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR4(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR3(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR3(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR2(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR2(base, x, ...) base{#x, x}, TROMPELOEIL_INIT_WITH_STR1(base, __VA_ARGS__)
#define TROMPELOEIL_INIT_WITH_STR1(base, x) base{#x, x}
#define TROMPELOEIL_INIT_WITH_STR0(base)
#define TROMPELOEIL_INIT_WITH_STR(base, ...) TROMPELOEIL_CONCAT(TROMPELOEIL_INIT_WITH_STR, TROMPELOEIL_COUNT(__VA_ARGS__))(base, __VA_ARGS__)

namespace trompeloeil
{
  class expectation_violation : public std::logic_error
  {
  public:
    using std::logic_error::logic_error;
  };

  enum class severity { fatal, nonfatal };

  inline
  std::function<void(severity, const std::string& loc, const std::string&)>& reporter_obj()
  {
    static std::function<void(severity, const std::string& loc, const std::string&)> obj
      = [](severity, const std::string& loc, const std::string& msg)
      {
        throw expectation_violation(loc + "\n" + msg);
      };
    return obj;
  }

  inline
  void set_reporter(std::function<void(severity, const std::string& loc, const std::string& s)> f)
  {
    reporter_obj() = f;
  }


  inline
  void send_report(severity s, const char* loc, const std::string& msg)
  {
    reporter_obj()(s, loc, msg);
  }

  template <typename T>
  class is_output_streamable
  {
    struct no;
    template <typename U>
    static no func(...);
    template <typename U>
    static auto func(U* u) -> decltype(std::declval<std::ostream&>() << *u);
  public:
    static const bool value = !std::is_same<no, decltype(func<T>(nullptr))>::value;
  };

  struct stream_sentry
  {
    stream_sentry(std::ostream& os_) : os(os_), width(os.width(0)), flags(os.flags(std::ios_base::dec | std::ios_base::left)), fill(os.fill(' ')) {  }
    ~stream_sentry() { os.flags(flags); os.fill(fill); os.width(width);}
    std::ostream& os;
    std::streamsize width;
    std::ios_base::fmtflags flags;
    char fill;
  };

  template <typename T, bool b = is_output_streamable<T>::value>
  struct streamer
  {
    static void print(std::ostream& os, const T& t)
    {
      stream_sentry s(os);
      os << t;
    }
  };


  template <typename T>
  struct streamer<T, false>
  {
    static void print(std::ostream& os, const T& t)
    {
      stream_sentry s(os);

      os << sizeof(T) << "-byte object={";
      if (sizeof(T) > 8) os << '\n';
      os << std::setfill('0') << std::hex;
      auto p = reinterpret_cast<const uint8_t*>(&t);
      for (size_t i = 0; i < sizeof(T); ++i)
      {
        os << " 0x" << std::setw(2) << unsigned(p[i]);
        if ((i & 0xf) == 0xf) os << '\n';
      }
      os << " }";
    }
  };
  template <typename T>
  void print(std::ostream& os, const T& t)
  {
    streamer<T>::print(os, t);
  }

  template<typename T>
  struct list_elem
  {
    list_elem(T *list) : n(list), p(list->p)
    {
      p->n = n->p = this;
      assert(list->p->n == list);
      assert(list->n->p == list);
      assert(n->p == this);
      assert(p->n == this);
    }

    list_elem() : n(this), p(this)
    {
    }

    list_elem(const list_elem &) = delete;

    list_elem(list_elem &&r) : n(r.n), p(r.p)
    {
      assert(r.n->p == &r);
      assert(r.p->n == &r);
      r.n = r.p = &r;
      n->p = p->n = this;
      assert(n->p == this);
      assert(p->n == this);
    }

    ~list_elem()
    {
      unlink();
    }

    list_elem &operator=(const list_elem &) = delete;
    list_elem &operator=(list_elem&&) = delete;

    bool is_empty() const
    {
      assert(n->p == this);
      assert(p->n == this);
      return n == this;
    }

    T       *next()       { return static_cast<T       *>(n); }
    T const *next() const { return static_cast<T const *>(n); }
    T       *prev()       { return static_cast<T       *>(p); }
    T const *prev() const { return static_cast<T const *>(p); }

    void unlink()
    {
      assert(n->p == this);
      assert(p->n == this);
      auto pp = p;
      auto nn = n;
      nn->p = pp;
      pp->n = nn;
      n = p = this;
      assert(pp->n == nn);
      assert(nn->p == pp);
    }

    void link_before(T &b)
    {
      auto nn = n;
      auto bn = b.n;
      nn->n = b.n;
      bn->p = nn;
      b.n = this;
      p = &b;
      assert(p->n == this);
      assert(n->p == this);
      assert(b.n->p == &b);
      assert(b.p->n == &b);
    };

    list_elem *n;
    list_elem *p;
  };

  struct sequence : public list_elem<sequence>
  {
    sequence() = default;
  protected:
    sequence(sequence* p) : list_elem(p) {}
  };

  struct sequence_elem : public sequence
  {
    sequence_elem(sequence& r) : sequence(&r) {}
  };

  struct sequence_matcher : public list_elem<sequence_matcher>
  {
    sequence_matcher(const char* name_, sequence& s) : name(name_), seq(s), seq_elem(s) {}
    void check_match(const char *match_name, const char* loc) const
    {
      if (seq.next() != &seq_elem)
      {
        std::ostringstream os;
        os << "Sequence mismatch of " << match_name
           << ". Sequence \"" << name
           << "\" was first in line for matching expectation\n";
        send_report(severity::fatal, loc, os.str());
      }
    }
    void retire() { seq_elem.unlink(); }
    const char    *name;
    sequence&      seq;
    sequence_elem  seq_elem;
  };

  struct wildcard
  {
    template<typename T>
    operator T&&() const;
    template<typename T>
    operator T&() const;
  };

  static constexpr const wildcard _{};

  template <typename T>
  struct typed_wildcard
  {
    operator T() const;
  };
  template<typename T>
  class optional
  {
  public:
    optional() : valid(false) { }

    optional(const T &t) : valid(true) { new(buffer) T(t);  }

    optional(T &&t) : valid(true) { new(buffer) T(std::move(t)); }

    optional(const optional &c) : valid(c.valid)
    {
      if (valid) new(buffer) T(c.value());
    }

    optional(optional &&c) : valid(c.valid)
    {
      if (valid) new(buffer) T(c.rvalue());
    }

    ~optional()
    {
      if (valid) value().~T();
    }

    optional &operator=(const optional &c)
    {
      if (&c != this)
      {
        if (valid) value().~T();
        valid = c.valid;
        if (valid) new(buffer)T(c.value());
      }
      return *this;
    }

    optional &operator=(optional &&c)
    {
      if (valid) value().~T();
      valid = c.valid;
      if (valid) new(buffer)T(std::move(c.rvalue()));
      return *this;
    }

    optional &operator=(const T &t)
    {
      return operator=(optional(t));
    }

    optional &operator=(T &&t)
    {
      return operator=(optional(std::move(t)));
    }

    const T &value() const
    {
      return *reinterpret_cast<const T *>(buffer);
    }

    T &value()
    {
      return *reinterpret_cast<T *>(buffer);
    }

    T &&rvalue()
    {
      return std::move(value());
    }

    bool is_valid() const { return valid; }

    operator T &()
    {
      return value();
    }
  private:
    alignas(T) char buffer[sizeof(T)];
    bool valid;
  };

  template <typename T>
  class optional<T&>
  {
  public:
    optional() = default;
    optional(T& t) : ptr(&t) {}
    const T& value() const { return *ptr; }
    T& value() { return *ptr; }
    bool is_valid() const { return ptr; }
    operator T&() { return value(); }
  private:
    T* ptr = nullptr;
  };

  template <typename T>
  class optional<T&&>
  {
  public:
    optional() = default;
    optional(T& t) : ptr(&t) {}
    const T& value() const { return *ptr; }
    T& value() { return *ptr; }
    bool is_valid() const { return ptr; }
    operator T&() { return value(); }
  private:
    T* ptr = nullptr;
  };

  template<typename T>
  struct value_matcher
  {
    template <typename U>
    friend struct value_matcher;
  public:
    value_matcher(const ::trompeloeil::wildcard&) { }

    value_matcher(const ::trompeloeil::typed_wildcard<T>&) {}

    template <typename U, typename = typename std::enable_if<std::is_same<wildcard, typename std::remove_cv<typename std::remove_reference<U>::type>::type>::value > >
    value_matcher(value_matcher<U>&&) {}

    template<typename U>
    value_matcher(U &&u) : desired(std::forward<U>(u))  { }

    template<typename U>
    bool operator==(const U &u) const
    {
      return !desired.is_valid() || desired.value() == u;
    }

    friend std::ostream &operator<<(std::ostream &os, const value_matcher &v)
    {
      if (!v.desired.is_valid()) return os << "_";
      print(os, v.desired.value());
      return os;
    }

  private:
    optional<T> desired;
  };

  template<typename T>
  struct type_catcher_t;

  template<typename T>
  struct type_catcher_t<void(T)>
  {
    using type = T;
    using ref_type = T &;
    using const_ref_type = const T &;
  };


  template <>
  struct type_catcher_t<void(void)>
  {
    using type = void;
    using ref_type = void;
    using const_ref_type = void;
  };

  template <typename T>
  struct type_catcher_t<void(T&&)>
  {
    using type = T&&;
    using ref_type = T&&;
  };
  template<typename T>
  using ref_type_catcher = typename type_catcher_t<T>::ref_type;
  template<typename T>
  using const_ref_type_catcher = typename type_catcher_t<T>::const_ref_type;
  template<typename T>
  using verbatim_type_catcher = typename type_catcher_t<T>::type;

  struct lifetime_monitor;


  template<typename T>
  class mocked_class : public T
  {
  protected:
    using trompeloeil_mocked_type = T;
    using T::T;
  public:
    ~mocked_class();
    void trompeloeil_deathwatch(const char *name, const char *loc) const
    {
      trompeloeil_deathwatch_loc = loc;
      trompeloeil_deathwatch_name = name;
    }
    void trompeloeil_expect_death(trompeloeil::lifetime_monitor* monitor) const
    {
      trompeloeil_lifetime_monitor = monitor;
    }
  private:
    mutable const char                    *trompeloeil_deathwatch_loc = nullptr;
    mutable const char                    *trompeloeil_deathwatch_name = nullptr;
    mutable trompeloeil::lifetime_monitor *trompeloeil_lifetime_monitor = nullptr;
  };

  struct lifetime_monitor
  {
    template <typename T>
    lifetime_monitor(const mocked_class<T>&obj,
                     const char* obj_name,
                     const char *loc)
      : location(loc),
        object(obj_name)
    {
      obj.trompeloeil_expect_death(this);
    }
    ~lifetime_monitor()
    {
      if (!died)
      {
        std::ostringstream os;
        os << "Object " << object << " is still alive";
        send_report(severity::nonfatal, location, os.str());
      }
    }
    void notify() { died = true; }
    bool died = false;
    const char *location;
    const char *object;
  };

  template <typename T>
  mocked_class<T>::~mocked_class()
  {
    if (trompeloeil_lifetime_monitor)
    {
      trompeloeil_lifetime_monitor->notify();
      return;
    }
    if (trompeloeil_deathwatch_loc)
    {
      std::ostringstream os;
      os << "Unexpected destruction of "
         << typeid(T).name() << "@" << this
         << " on deathwatch as " << trompeloeil_deathwatch_name  << '\n';
      trompeloeil::send_report(trompeloeil::severity::nonfatal,
                             trompeloeil_deathwatch_loc,
                             os.str());
    }
  };

  template<typename T>
  struct return_of_t;

  template<typename R, typename ... A>
  struct return_of_t<R(A...)>
  {
    using type = R;
  };

  template<typename T>
  using return_of = typename return_of_t<T>::type;

  template<typename T>
  struct call_match_type_t;

  template<typename R, typename ... T>
  struct call_match_type_t<R(T...)>
  {
    using type = std::tuple<typename std::add_lvalue_reference<T>::type...>;
  };

  template<typename T>
  using call_match_type = typename call_match_type_t<T>::type;

  template<typename T>
  struct value_match_type_t;

  template<typename R, typename ... T>
  struct value_match_type_t<R(T...)>
  {
    using type = std::tuple<value_matcher<T> ...>;
  };


  template<typename Sig>
  using value_match_type = typename value_match_type_t<Sig>::type;


  template<typename T>
  struct call_action_type_t;

  template<typename R, typename ... T>
  struct call_action_type_t<R(T...)>
  {
    using type = std::tuple<typename std::add_lvalue_reference<T>::type ...>;
  };

  template<typename Sig>
  using call_action_type = typename call_action_type_t<Sig>::type;

  template<typename Sig>
  struct call_matcher_base : public list_elem<call_matcher_base<Sig> >
  {
    using param_type = call_match_type<Sig>;
    call_matcher_base() = default;

    call_matcher_base(call_matcher_base *list)
      : list_elem<call_matcher_base>(list)
    {
    }

    virtual bool matches(const param_type &) const = 0;
    virtual bool run_actions(call_action_type<Sig> &params) = 0;
    virtual std::ostream& report_mismatch(std::ostream&,const param_type &) = 0;
    virtual return_of<Sig> return_value(call_action_type<Sig> &params) = 0;
    virtual void report_missed() = 0;
  };

  template<typename ... A>
  struct call_matcher_base<void(A...)>
    : public list_elem<call_matcher_base<void(A...)> >
  {
    using param_type = call_match_type<void(A...)>;

    call_matcher_base() = default;

    call_matcher_base(call_matcher_base *list)
      : list_elem<call_matcher_base>(list)
    {
    }

    virtual bool matches(const param_type &) const = 0;
    virtual bool run_actions(call_action_type<void(A...)> &params) = 0;
    virtual std::ostream& report_mismatch(std::ostream&, const param_type &) = 0;
    void return_value(call_action_type<void(A...)> &) {};

    virtual void report_missed() = 0;

  };

  template<typename T, size_t N = 0, bool b = N == std::tuple_size<T>::value>
  struct tuple_pair
  {
    template <typename stream>
    static stream &print_mismatch(stream &os, const T &t1, const T &t2)
    {
      os << "  Got param _" << N+1 << " = ";
      print(os, std::get<N>(t1));
      os << "\n  Expected:     ";
      print(os, std::get<N>(t2));
      os << "\n\n";

      return tuple_pair<T, N + 1>::print_mismatch(os, t1, t2);
    }

    template <typename stream>
    static stream &print_missed(stream &os, const T &t)
    {
      os << "  param _" << N+1 << " = ";
      print(os, std::get<N>(t));
      os << '\n';
      return tuple_pair<T, N + 1>::print_missed(os, t);
    }
  };

  template<typename T, size_t N>
  struct tuple_pair<T, N, true>
  {
    template <typename stream>
    static stream &print_mismatch(stream &os, const T &, const T &)
    {
      return os;
    }

    template <typename stream>
    static stream& print_missed(stream &os, const T &)
    {
      return os;
    }
  };

  template <typename T, typename ... A>
  struct all_are;

  template <typename T>
  struct all_are<T> : public std::true_type {};

  template <typename T, typename ... A>
  struct all_are<T, T, A...> : public all_are<T, A...> {};

  template <typename T, typename U, typename ... A>
  struct all_are<T, U, A...> : public std::false_type {};

  template<typename Sig>
  struct call_matcher_list : public call_matcher_base<Sig>
  {
    using typename call_matcher_base<Sig>::param_type;

    template<typename ... U>
    call_matcher_list &operator()(const U &...) { return *this; }

    virtual bool matches(const param_type &) const { return false; }

    virtual bool run_actions(call_action_type<Sig> &) { return false; }

    virtual std::ostream& report_mismatch(std::ostream& r, const param_type &) override { return r;}

    virtual return_of<Sig> return_value(call_action_type<Sig> &)
    {
      typename std::remove_reference<return_of<Sig>>::type *p = nullptr;
      return std::forward<return_of<Sig>>(*p);
    }

    virtual void report_missed() {}
  };

  template<typename ... A>
  struct call_matcher_list<void(A...)> : public call_matcher_base<void(A...)>
  {
    using typename call_matcher_base<void(A...)>::param_type;

    template<typename ... U>
    call_matcher_list &operator()(const U &...) { return *this;}
    virtual bool matches(const param_type &) const { return false; }
    virtual bool run_actions(call_action_type<void(A...)> &) { return false;}
    virtual std::ostream& report_mismatch(std::ostream& r, const param_type &) override {return r;}
    virtual void report_missed() {}
  };

  template <typename Sig>
  call_matcher_base<Sig>* find(const typename call_matcher_base<Sig>::param_type& p,
                               call_matcher_list<Sig>& list)
  {
    for (auto i = list.prev(); i != &list; i = i->prev())
    {
      if (i->matches(p))
      {
        return i;
      }
    }
    return nullptr;
  }

  template <typename Sig>
  void report_mismatch(const char *name,
                       const typename call_matcher_base<Sig>::param_type& p,
                       call_matcher_list<Sig>& matcher_list,
                       call_matcher_list<Sig>& exhausted_list)
  {
    std::ostringstream os;
    os << "No match for call " << name << ".\n";
    bool exhausted_match = false;
    for (auto i = exhausted_list.next(); i != &exhausted_list; i = i->next())
    {
      if (i->matches(p))
      {
        exhausted_match = true;
        os << "Matches exhausted call requirement\n";
        i->report_mismatch(os, p);
      }
    }
    if (!exhausted_match)
    {
      for (auto i = matcher_list.next(); i != &matcher_list; i = i->next())
      {
        os << "Tried ";
        i->report_mismatch(os, p);
      }
    }
    send_report(severity::fatal, "", os.str());
  }

  template<typename Sig>
  struct condition_base : public list_elem<condition_base<Sig> >
  {
    condition_base() = default;
    condition_base(condition_base&& r) : list_elem<condition_base<Sig> >(std::move(r)) {}
    virtual bool check(const typename call_matcher_base<Sig>::param_type &) const = 0;
  };

  template<typename Sig>
  struct condition_list : public condition_base<Sig>
  {
    condition_list() = default;
    condition_list(condition_list&& r) : condition_base<Sig>(std::move(r)) {}
    bool check(const typename call_matcher_base<Sig>::param_type &) const override
    {
      return false;
    }
  };

  template<typename Sig, typename Cond>
  struct condition : public condition_base<Sig>
  {
    condition(const char *str_, Cond c_) : c(c_), str(str_) {};

    bool check(const typename call_matcher_base<Sig>::param_type &t) const override
    {
      return c(t);
    }

    Cond c;
    const char *str;
  };


  template<typename Sig>
  struct side_effect_base : public list_elem<side_effect_base<Sig> >
  {
    virtual void action(call_action_type<Sig> &) = 0;
  };

  template<typename Sig>
  struct side_effect_list : public side_effect_base<Sig>
  {
    void action(call_action_type<Sig> &) {}
  };

  template<typename Sig, typename Action>
  struct side_effect : public side_effect_base<Sig>
  {
    side_effect(const char *str_, Action a_) : a(a_), str(str_) {};

    void action(call_action_type<Sig> &t) { a(t); }

    Action a;
    const char *str;
  };

  template<typename Sig>
  struct return_handler_base : public list_elem<return_handler_base<Sig> >
  {
    virtual return_of<Sig> return_value(call_action_type<Sig> &) = 0;
  };

  template<typename Sig>
  struct return_handler_list : public return_handler_base<Sig>
  {
    return_of<Sig> return_value(call_action_type<Sig> &)
    {
      typename std::remove_reference<return_of<Sig>>::type *p = nullptr;
      return std::forward<return_of<Sig> >(*p);
    }
  };

  template<typename ... A>
  struct return_handler_list<void(A...)>
    : public return_handler_base<void(A...)>
  {
    void return_value(call_action_type<void(A...)> &) {}
  };

  template<typename Sig, typename Handler>
  struct return_handler : public return_handler_base<Sig>
  {
    return_handler(const char *str_, Handler h_) : h(h_), str(str_) {}

    return_of<Sig> return_value(call_action_type<Sig> &t) { return h(t); }

    Handler h;
    const char *str;
  };

  template <typename T, std::size_t N, size_t M>
  struct sequence_validator_t;

  template <typename ... T, size_t N, size_t M>
  struct sequence_validator_t<std::tuple<T...>, N, M>
  {
    static void validate(const char*match_name, const char *loc, const std::tuple<T...>& t)
    {
      std::get<N>(t).check_match(match_name, loc);
      sequence_validator_t<std::tuple<T...>, N + 1, M>::validate(match_name, loc, t);
    }
    static void retire(std::tuple<T...>& t)
    {
      std::get<N>(t).retire();
      sequence_validator_t<std::tuple<T...>, N + 1, M>::retire(t);
    }
  };

  template <typename ... T, size_t N>
  struct sequence_validator_t<std::tuple<T...>, N, N>
  {
    static void validate(const char*, const char*, const std::tuple<T...>& ) {}
    static void retire(std::tuple<T...>& ){}
  };


  template <typename T>
  struct sequence_validator
  : sequence_validator_t<T, 0, std::tuple_size<T>::value>
  {
  };

  struct sequence_handler_base : public list_elem<sequence_handler_base >
  {
    virtual void validate(const char*, const char*) = 0;
    virtual void retire() = 0;
  };

  struct sequence_handler_list : public sequence_handler_base
  {
    void validate(const char*, const char*) override {}
    void retire() override {}
  };


  template <typename T>
  struct sequence_handler;

  template <typename ... Seq>
  struct sequence_handler<std::tuple<Seq...> > : public sequence_handler_base
  {
    using seq_tuple = std::tuple<Seq...>;
    sequence_handler(seq_tuple&& t) : sequences(std::move(t)) {}
    void validate(const char* match_name, const char *loc)
    {
      sequence_validator<seq_tuple>::validate(match_name, loc, sequences);
    }
    void retire()
    {
      sequence_validator<seq_tuple>::retire(sequences);
    }
    seq_tuple sequences;
  };

  template<typename R, typename P>
  struct return_type_injector : public P
  {
    using return_type = R;
    using P::P;

    template<typename ... A>
    return_type_injector(A &&... a) : P(std::forward<A>(a)...) {}
  };

  template <typename P>
  struct call_limit_injector : public P
  {
    static const bool call_limit_set = true;
    using P::P;

    template <typename ... A>
     call_limit_injector(A && ... a) : P(std::forward<A>(a)...) {}
  };

  template <typename P>
  struct sequence_injector : public P
  {
    static const bool sequence_set = true;
    using P::P;
    template <typename ... A>
    sequence_injector(A&& ... a) : P(std::forward<A>(a)...) {}
  };
  template <typename Parent, typename U, typename Sig>
  struct call_data : public Parent
  {
    using typename Parent::return_type;
    using Parent::call_limit_set;
    using Parent::sequence_set;
    call_data(Parent&& p) : Parent(std::move(p)) {}
    call_data(Parent&& p, U&& d) : Parent(std::move(p)), data(std::move(d))
    {
      add_last(data);
    }
    void add_last(side_effect_base<Sig>& s)
    {
      this->actions.link_before(s);
    }
    void add_last(condition_base<Sig>& s)
    {
      this->conditions.link_before(s);
    }
    void add_last(return_handler_base<Sig>& s)
    {
      this->return_handler.link_before(s);
    }
    void add_last(sequence_handler_base& s)
    {
      this->sequence_handler.link_before(s);
    }
    void add_last(std::tuple<>) {}
    template <typename D>
    call_data<call_data, condition<Sig, D>, Sig> with(const char* str, D&& d)
    {
      return {std::move(*this), condition<Sig, D>(str, std::move(d))};
    }
    template <typename A>
    call_data<call_data, side_effect<Sig, A>, Sig> sideeffect(const char* str, A&& a)
    {
      return {std::move(*this), side_effect<Sig, A>(str, std::move(a))};
    }
    template <typename H>
    call_data<return_type_injector<return_of<Sig>, call_data>, return_handler<Sig, H>, Sig> handle_return(const char* str, H&& h)
    {
      static_assert(std::is_constructible<return_of<Sig>, decltype(h(std::declval<call_action_type<Sig>& >()))>::value || !std::is_same<return_of<Sig>, void>::value,
                    "RETURN does not make sense for void-function");
      static_assert(std::is_constructible<return_of<Sig>, decltype(h(std::declval<call_action_type<Sig>& >()))>::value || std::is_same<return_of<Sig>, void>::value,
                    "given RETURN type is not convertible to that of the function");
      static_assert(!std::is_same<return_type, decltype(h(std::declval<call_action_type<Sig>&>()))>::value || std::is_same<return_type, void>::value,
                    "A RETURN is already given");
      return {return_type_injector<return_of<Sig>, call_data>(std::move(*this)), return_handler<Sig, H>(str, std::move(h))};
    }
    template <unsigned long long L,
              unsigned long long H = L,
              bool               verboten = call_limit_set>
    call_data<call_limit_injector<call_data>, std::tuple<>, Sig> times()
    {
      static_assert(!verboten,
                    "A TIMES call limit is already given");
      static_assert(H >= L, "In TIMES Higher limit must exceed lower limit");
      this->min_calls = L;
      this->max_calls = H;
      return { std::move(*this), {} };
    }

    template <typename ... T, bool b = sequence_set, typename = std::enable_if<all_are<sequence_matcher, T...>::value> >
    call_data<sequence_injector<call_data>,sequence_handler<std::tuple<T...> >,Sig> in_sequence(T&& ... t)
    {
      static_assert(!b, "a SEQUENCE limit is already in place");
      return { std::move(*this), { std::tuple<typename std::remove_reference<T>::type...>(std::forward<T>(t)...) } };
    }

    U data;
  };

  struct expectation {
    virtual ~expectation() = default;
  };

  template<typename Sig>
  struct call_matcher : public call_matcher_base<Sig>, expectation
  {
    using return_type = void;
    using param_type = typename call_matcher_base<Sig>::param_type;

    template<typename ... U>
    call_matcher(U &&... u) : val(value_matcher<U>(std::forward<U>(u))...) {}

    call_matcher(call_matcher &&r) = default;

    ~call_matcher()
    {
      if (!reported && !this->is_empty() && call_count < min_calls) report_missed();
    }

    call_matcher& hook_last(call_matcher_list<Sig> &list)
    {
      list.link_before(*this);
      return *this;
    }

    virtual bool matches(const param_type& params) const override
    {
      return val == params && match_conditions(params);
    }

    bool match_conditions(const param_type& params) const
    {
      for (auto p = conditions.next(); p != &conditions; p = p->next())
      {
        if (!p->check(params)) return false;
      }
      return true;
    }

    return_of<Sig> return_value(call_action_type<Sig>& params)
    {
      return return_handler.next()->return_value(params);
    }
    bool run_actions(call_action_type<Sig>& params)
    {
      auto limits = call_limits();
      if (call_count < std::get<0>(limits))
      {
        sequence_handler.next()->validate(name, location);
      }
      if (++call_count > std::get<1>(limits))
      {
        reported = true;
        std::ostringstream os;
        if (std::get<1>(limits) == 0)
        {
          os << "Match of forbidden call of" << name << "\n";
        }
        else
        {
          os << "Expectation fulfilled " << name << " " << call_count << " times when the limit is "
             << std::get<1>(limits) << "\n";
        }
        tuple_pair<decltype(val)>::print_missed(os, params);
        send_report(severity::fatal, location, os.str());
      }
      if (call_count == std::get<0>(limits))
      {
        sequence_handler.next()->retire();
      }
      for (auto p = actions.next(); p != &actions; p = p->next())
      {
        p->action(params);
      }
      return call_count == std::get<1>(limits);
    }
    std::ostream& report_mismatch(std::ostream& os, const param_type& params) override
    {
      reported = true;
      os << "No matching call for expectation of " << name << " at " << location << "\n";
      return tuple_pair<decltype(val)>::print_mismatch(os, params, val);
    }

    void report_missed() override
    {
      reported = true;
      std::ostringstream os;
      os << "Unfulfilled expectation:\n"
         << "Expected " << name << " to be called " << min_calls
         << " times, actually called " << call_count << " time"
         << (call_count > 1 ? "s\n" : "\n");
      tuple_pair<decltype(val)>::print_missed(os, val);
      send_report(severity::nonfatal, location, os.str());
    }
    template <typename D>
    call_data<call_matcher, condition<Sig, D>, Sig> with(const char* str, D&& d)
    {
      return { std::move(*this), condition<Sig, D>(str, std::move(d)) };
    }
    template <typename A>
    call_data<call_matcher, side_effect<Sig, A>, Sig> sideeffect(const char* str, A&& a)
    {
      return {std::move(*this), side_effect<Sig, A>(str, std::move(a))};
    }

    template <typename H>
    call_data<return_type_injector<return_of<Sig>, call_matcher>, return_handler<Sig, H>, Sig> handle_return(const char* str, H&& h)
    {
      static_assert(!std::is_same<return_of<Sig>, void>::value || std::is_same<H, void>::value,
                    "RETURN does not make sense for void-function");
#if 0
      static_assert(std::is_constructible<return_of<Sig>, decltype(h(std::declval<call_action_type<Sig> >()))>::value || std::is_same<return_of<Sig>, void>::value,
                    "given RETURN type is not convertible to that of the function");
#endif
      return {std::move(*this), {str, std::move(h)}};
    }
    template <unsigned long long L, unsigned long long H = L>
    call_data<call_limit_injector<call_matcher>, std::tuple<>, Sig> times()
    {
      static_assert(H >= L, "In TIMES Higher limit must exceed lower limit");
      min_calls = L;
      max_calls = H;
      return { std::move(*this), {} };
    }

    template <typename ... T, typename = std::enable_if<all_are<sequence_matcher, T...>::value> >
    call_data<sequence_injector<call_matcher>,sequence_handler<std::tuple<T...> >,Sig> in_sequence(T&& ... t)
    {
      std::tuple<T...> tup(std::forward<T>(t)...);
      using h = ::trompeloeil::sequence_handler<std::tuple<T...> >;
      return { std::move(*this), h( std::move(tup) ) };
    }
    call_matcher &set_location(const char *loc)
    {
      location = loc;
      return *this;
    }
    call_matcher& set_name(const char* n)
    {
      name = n;
      return *this;
    }
    virtual std::tuple<unsigned long long, unsigned long long> call_limits() const
    {
      return std::make_tuple(min_calls, max_calls);
    }

    static const bool         call_limit_set = false;
    static const bool         sequence_set = false;
    value_match_type<Sig>     val;
    condition_list<Sig>       conditions;
    side_effect_list<Sig>     actions;
    return_handler_list<Sig>  return_handler;
    sequence_handler_list     sequence_handler;
    const char               *location;
    const char               *name;
    unsigned long long        call_count = 0;
    unsigned long long        min_calls = 1;
    unsigned long long        max_calls = 1;
    bool                      reported = false;
  };


  template <typename T, int N, bool b = N <= std::tuple_size<T>::value>
  struct arg
  {
    static typename std::tuple_element<N - 1,T>::type value(T& t)
    {
      return std::get<N - 1>(t);
    }
  };

  template <int N>
  struct illegal_argument {};

  template <typename T, int N>
  struct arg<T, N, false>
  {
    static const illegal_argument<N>& value(T&)
    {
      static const constexpr illegal_argument<N> v{};
      return v;
    }

  };

  template <int N, typename T>
  auto mkarg(T& t) -> decltype(arg<T, N>::value(t)) { return arg<T, N>::value(t); }

  template <typename ... T>
  void ignore(const T& ...) {}

  template <typename ... T>
  call_match_type<void(T...)> make_value_match_obj(T&& ... t)
  {
    call_match_type<void(T...)> rv{t...};
    return rv;
  }

  template <typename ... T>
  call_action_type<void(T...)> make_action_type_obj(T&& ... t)
  {
    return call_action_type<void(T...)>(t...);
  }

  struct call_validator
  {
    template <typename Sig>
    call_matcher<Sig> operator+(trompeloeil::call_matcher<Sig>& t) {
      static_assert(std::is_same<typename call_matcher<Sig>::return_type, return_of<Sig> >::value,
                    "missig RETURN for non-void function");
      return std::move(t);
    }
    template <typename P, typename U, typename Sig>
    call_data<P, U, Sig> operator+(::trompeloeil::call_data<P, U, Sig>&& t) {
      static_assert(std::is_same<return_of<Sig>, typename call_data<P, U, Sig>::return_type>::value,
                    "RETURN missing for non-void function");
      return std::move(t);
    }
  };

  struct heap_elevator
  {
    template <typename T>
    std::unique_ptr<T> operator^(T&& t)
    {
      return std::unique_ptr<T>(new T(std::move(t)));
    }
  };
}

#define TROMPELOEIL_MOCK(name, params)          \
  TROMPELOEIL_MOCK_(name, , params)

#define TROMPELOEIL_MOCK_CONST(name, params)    \
  TROMPELOEIL_MOCK_(name, const, params)



#define TROMPELOEIL_MOCK_(name, constness, params)                            \
  using TROMPELOEIL_CONCAT(trompeloeil_matcher_type_, __LINE__) =             \
    ::trompeloeil::call_matcher<decltype(std::declval<trompeloeil_mocked_type>()          \
                                         .name( TROMPELOEIL_VLIST params)) params>;       \
                                                                              \
  TROMPELOEIL_CONCAT(trompeloeil_matcher_type_, __LINE__)                     \
  trompeloeil_matcher_type_ ## name params constness;                         \
                                                                              \
  using TROMPELOEIL_CONCAT(trompeloeil_matcher_list_type_, __LINE__) =        \
    ::trompeloeil::call_matcher_list<decltype(std::declval<trompeloeil_mocked_type>()     \
                                              .name( TROMPELOEIL_VLIST params)) params>;  \
                                                                              \
  mutable TROMPELOEIL_CONCAT(trompeloeil_matcher_list_type_, __LINE__)        \
    TROMPELOEIL_CONCAT(trompeloeil_matcher_list_, __LINE__);                  \
                                                                              \
  mutable TROMPELOEIL_CONCAT(trompeloeil_matcher_list_type_, __LINE__)        \
    TROMPELOEIL_CONCAT(trompeloeil_exhausted_matcher_list_, __LINE__);        \
                                                                              \
  struct TROMPELOEIL_CONCAT(tag_type_trompeloeil_, __LINE__)                  \
  {                                                                           \
    using name = TROMPELOEIL_CONCAT(trompeloeil_matcher_type_, __LINE__);     \
  };                                                                          \
  TROMPELOEIL_CONCAT(tag_type_trompeloeil_, __LINE__)                         \
  trompeloeil_tag_ ## name params constness;                                  \
                                                                              \
  TROMPELOEIL_CONCAT(trompeloeil_matcher_list_type_, __LINE__)&               \
  trompeloeil_matcher_list(TROMPELOEIL_CONCAT(tag_type_trompeloeil_, __LINE__)) constness \
  {                                                                           \
    return TROMPELOEIL_CONCAT(trompeloeil_matcher_list_, __LINE__);           \
  }                                                                           \
  auto name (VERBATIM_TROMPELOEIL_PLIST params) constness                     \
  -> decltype(trompeloeil_mocked_type::name TROMPELOEIL_CLIST params) override            \
  {                                                                           \
    const auto param_value = ::trompeloeil::make_value_match_obj TROMPELOEIL_CLIST params;  \
    auto i = find(param_value, TROMPELOEIL_CONCAT(trompeloeil_matcher_list_, __LINE__)); \
    if (!i) \
    {                                                                         \
      ::trompeloeil::report_mismatch(#name #params,                     \
                                     param_value,                       \
                                     TROMPELOEIL_CONCAT(trompeloeil_matcher_list_, __LINE__), \
                                     TROMPELOEIL_CONCAT(trompeloeil_exhausted_matcher_list_, __LINE__)); \
    }                                                                         \
    auto param_ref = ::trompeloeil::make_action_type_obj TROMPELOEIL_CLIST params;        \
    if (i->run_actions(param_ref))                                            \
    {                                                                 \
      i->unlink();                                                      \
      TROMPELOEIL_CONCAT(trompeloeil_exhausted_matcher_list_, __LINE__).link_before(*i); \
    }                                                                   \
    return i->return_value(param_ref);                                        \
  }

#define TROMPELOEIL_STRINGIFY_(...) #__VA_ARGS__
#define TROMPELOEIL_STRINGIFY(...) TROMPELOEIL_STRINGIFY_(__VA_ARGS__)

#define TROMPELOEIL_REQUIRE_CALL(obj, func) \
  auto TROMPELOEIL_CONCAT(call_obj, __COUNTER__) =  TROMPELOEIL_REQUIRE_CALL_OBJ(obj, func)


#define TROMPELOEIL_NAMED_REQUIRE_CALL(obj, func) \
  ::trompeloeil::heap_elevator{} ^ TROMPELOEIL_REQUIRE_CALL_OBJ(obj, func)

#define TROMPELOEIL_REQUIRE_CALL_OBJ(obj, func)                         \
  ::trompeloeil::call_validator{} +                                     \
  decltype((obj).TROMPELOEIL_CONCAT(trompeloeil_tag_, func) )::func     \
  .set_location(__FILE__ ":" TROMPELOEIL_STRINGIFY(__LINE__))           \
  .set_name(#obj "." #func)                                             \
  .hook_last((obj).trompeloeil_matcher_list(decltype(TROMPELOEIL_CONCAT((obj).trompeloeil_tag_, func)){}))


#define TROMPELOEIL_ALLOW_CALL(obj, func) \
  TROMPELOEIL_REQUIRE_CALL(obj, func).TIMES(0, ~0ULL)


#define TROMPELOEIL_NAMED_ALLOW_CALL(obj, func) \
  TROMPELOEIL_NAMED_REQUIRE_CALL(obj, func).TIMES(0, ~0ULL)


#define TROMPELOEIL_FORBID_CALL(obj, func) \
  TROMPELOEIL_REQUIRE_CALL(obj, func).TIMES(0)

#define TROMPELOEIL_NAMED_FORBID_CALL(obj, func) \
  TROMPELOEIL_NAMED_REQUIRE_CALL(obj, func).TIMES(0)


#define TROMPELOEIL_WITH(...) with(#__VA_ARGS__, [&](const auto& x) { \
  auto& _1 = ::trompeloeil::mkarg<1>(x);                    \
  auto& _2 = ::trompeloeil::mkarg<2>(x);                    \
  auto& _3 = ::trompeloeil::mkarg<3>(x);                    \
  auto& _4 = ::trompeloeil::mkarg<4>(x);                    \
  auto& _5 = ::trompeloeil::mkarg<5>(x);                    \
  auto& _6 = ::trompeloeil::mkarg<6>(x);                    \
  auto& _7 = ::trompeloeil::mkarg<7>(x);                    \
  auto& _8 = ::trompeloeil::mkarg<8>(x);                    \
  auto& _9 = ::trompeloeil::mkarg<9>(x);                    \
  auto&_10 = ::trompeloeil::mkarg<10>(x);                   \
  auto&_11 = ::trompeloeil::mkarg<11>(x);                   \
  auto&_12 = ::trompeloeil::mkarg<12>(x);                   \
  auto&_13 = ::trompeloeil::mkarg<13>(x);                   \
  auto&_14 = ::trompeloeil::mkarg<14>(x);                   \
  auto&_15 = ::trompeloeil::mkarg<15>(x);                   \
  ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
  return __VA_ARGS__;\
  })


#define TROMPELOEIL_SIDE_EFFECT(...) sideeffect(#__VA_ARGS__, [&](auto& x) { \
  auto& _1 = ::trompeloeil::mkarg<1>(x);                    \
  auto& _2 = ::trompeloeil::mkarg<2>(x);                    \
  auto& _3 = ::trompeloeil::mkarg<3>(x);                    \
  auto& _4 = ::trompeloeil::mkarg<4>(x);                    \
  auto& _5 = ::trompeloeil::mkarg<5>(x);                    \
  auto& _6 = ::trompeloeil::mkarg<6>(x);                    \
  auto& _7 = ::trompeloeil::mkarg<7>(x);                    \
  auto& _8 = ::trompeloeil::mkarg<8>(x);                    \
  auto& _9 = ::trompeloeil::mkarg<9>(x);                    \
  auto&_10 = ::trompeloeil::mkarg<10>(x);                   \
  auto&_11 = ::trompeloeil::mkarg<11>(x);                   \
  auto&_12 = ::trompeloeil::mkarg<12>(x);                   \
  auto&_13 = ::trompeloeil::mkarg<13>(x);                   \
  auto&_14 = ::trompeloeil::mkarg<14>(x);                   \
  auto&_15 = ::trompeloeil::mkarg<15>(x);                   \
  ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
  __VA_ARGS__;\
  })


#define TROMPELOEIL_RETURN(...) handle_return(#__VA_ARGS__, [&](auto& x) {   \
  auto& _1 = ::trompeloeil::mkarg<1>(x);                                     \
  auto& _2 = ::trompeloeil::mkarg<2>(x);                                     \
  auto& _3 = ::trompeloeil::mkarg<3>(x);                                     \
  auto& _4 = ::trompeloeil::mkarg<4>(x);                                     \
  auto& _5 = ::trompeloeil::mkarg<5>(x);                                     \
  auto& _6 = ::trompeloeil::mkarg<6>(x);                                     \
  auto& _7 = ::trompeloeil::mkarg<7>(x);                                     \
  auto& _8 = ::trompeloeil::mkarg<8>(x);                                     \
  auto& _9 = ::trompeloeil::mkarg<9>(x);                                     \
  auto&_10 = ::trompeloeil::mkarg<10>(x);                                    \
  auto&_11 = ::trompeloeil::mkarg<11>(x);                                    \
  auto&_12 = ::trompeloeil::mkarg<12>(x);                                    \
  auto&_13 = ::trompeloeil::mkarg<13>(x);                                    \
  auto&_14 = ::trompeloeil::mkarg<14>(x);                                    \
  auto&_15 = ::trompeloeil::mkarg<15>(x);                                    \
  ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
  return __VA_ARGS__;                                                      \
    })


#define TROMPELOEIL_TIMES(...) times<__VA_ARGS__>()

#define TROMPELOEIL_IN_SEQUENCE(...) \
  in_sequence(TROMPELOEIL_INIT_WITH_STR(::trompeloeil::sequence_matcher, __VA_ARGS__))

#define TROMPELOEIL_ANY(type) ::trompeloeil::typed_wildcard<type>()

#define TROMPELOEIL_AT_LEAST(num) num, ~0ULL
#define TROMPELOEIL_AT_MOST(num) 0, num

#define TROMPELOEIL_DEATHWATCH(obj) \
  (obj).trompeloeil_deathwatch(#obj, __FILE__ ":" TROMPELOEIL_STRINGIFY(__LINE__))

#define TROMPELOEIL_REQUIRE_DESTRUCTION(obj) \
  ::trompeloeil::lifetime_monitor TROMPELOEIL_CONCAT(trompeloeil_death_monitor_, __LINE__)(obj, #obj, __FILE__ ":" TROMPELOEIL_STRINGIFY(__LINE__))

#define TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION(obj) \
  std::unique_ptr<::trompeloeil::lifetime_monitor>(new ::trompeloeil::lifetime_monitor(obj, #obj, __FILE__ ":" TROMPELOEIL_STRINGIFY(__LINE__)))

#ifndef TROMPELOEIL_LONG_MACROS
#define MOCK(name, params)            TROMPELOEIL_MOCK(name, params)
#define MOCK_CONST(name, params)      TROMPELOEIL_MOCK_CONST(name, params)
#define REQUIRE_CALL(obj, func)       TROMPELOEIL_REQUIRE_CALL(obj, func)
#define NAMED_REQUIRE_CALL(obj, func) TROMPELOEIL_NAMED_REQUIRE_CALL(obj, func)
#define ALLOW_CALL(obj, func)         TROMPELOEIL_ALLOW_CALL(obj, func)
#define NAMED_ALLOW_CALL(obj, func)   TROMPELOEIL_NAMED_ALLOW_CALL(obj, func)
#define FORBID_CALL(obj, func)        TROMPELOEIL_FORBID_CALL(obj, func)
#define NAMED_FORBID_CALL(obj, func)  TROMPELOEIL_NAMED_FORBID_CALL(obj, func)
#define WITH(...)                     TROMPELOEIL_WITH(__VA_ARGS__)
#define SIDE_EFFECT(...)              TROMPELOEIL_SIDE_EFFECT(__VA_ARGS__)
#define RETURN(...)                   TROMPELOEIL_RETURN(__VA_ARGS__)
#define TIMES(...)                    TROMPELOEIL_TIMES(__VA_ARGS__)
#define IN_SEQUENCE(...)              TROMPELOEIL_IN_SEQUENCE(__VA_ARGS__)
#define ANY(type)                     TROMPELOEIL_ANY(type)
#define AT_LEAST(num)                 TROMPELOEIL_AT_LEAST(num)
#define AT_MOST(num)                  TROMPELOEIL_AT_MOST(num)
#define REQUIRE_DESTRUCTION(obj)      TROMPELOEIL_REQUIRE_DESTRUCTION(obj)
#define DEATHWATCH(obj)               TROMPELOEIL_DEATHWATCH(obj)
#define NAMED_REQUIRE_DESTRUCTION(obj)TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION(obj)
#endif

#endif // include guard

