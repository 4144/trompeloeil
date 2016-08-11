/*
 * Trompeloeil C++ mocking framework
 *
 * Copyright Björn Fahller 2014-2016
 *
 *  Use, modification and distribution is subject to the
 *  Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 *
 * Project home: https://github.com/rollbear/trompeloeil
 */

#ifndef TROMPELOEIL_HPP_
#define TROMPELOEIL_HPP_


// trompe l'oeil noun    (Concise Encyclopedia)
// Style of representation in which a painted object is intended
// to deceive the viewer into believing it is the object itself...

// project home: https://github.com/rollbear/trompeloeil


// Deficiencies and missing features
// * Mocking function templates is not supported
// * If a macro kills a kitten, this threatens extinction of all felines!

#if defined(_MSC_VER)
#  define TROMPELOEIL_NORETURN
#  if (!defined(__cplusplus) || _MSC_VER < 1900)
#    error requires C++ in Visual Studio 2015 RC or later
#  endif
#else
#  define TROMPELOEIL_NORETURN [[noreturn]]
#  if (!defined(__cplusplus) || __cplusplus <= 201103)
#    error requires C++14 or higher
#  endif
#endif
#include <tuple>
#include <iomanip>
#include <sstream>
#include <exception>
#include <functional>
#include <memory>
#include <cstring>
#include <regex>
#include <mutex>

#ifdef TROMPELOEIL_SANITY_CHECKS
#include <cassert>
#define TROMPELOEIL_ASSERT(x) assert(x)
#else
#define TROMPELOEIL_ASSERT(x) do {} while (false)
#endif

#define TROMPELOEIL_IDENTITY(...) __VA_ARGS__ // work around stupid MS VS2015 RC bug

#define TROMPELOEIL_ARG16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15, ...) _15

#define TROMPELOEIL_COUNT(...)                                                 \
  TROMPELOEIL_IDENTITY(TROMPELOEIL_ARG16(__VA_ARGS__,                          \
                                         15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))

#define TROMPELOEIL_CONCAT_(x, y) x ## y
#define TROMPELOEIL_CONCAT(x, y) TROMPELOEIL_CONCAT_(x, y)

#define TROMPELOEIL_INIT_WITH_STR15(base, x, ...)                              \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR14(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR14(base, x, ...)                              \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR13(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR13(base, x, ...)                              \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR12(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR12(base, x, ...)                              \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR11(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR11(base, x, ...)                              \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR10(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR10(base, x, ...)                              \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR9(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR9(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR8(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR8(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR7(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR7(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR6(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR6(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR5(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR5(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR4(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR4(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR3(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR3(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR2(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR2(base, x, ...)                               \
  base{#x, x}, TROMPELOEIL_INIT_WITH_STR1(base, __VA_ARGS__)

#define TROMPELOEIL_INIT_WITH_STR1(base, x)                                    \
  base{#x, x}

#define TROMPELOEIL_INIT_WITH_STR0(base)

#define TROMPELOEIL_INIT_WITH_STR(base, ...)                                   \
  TROMPELOEIL_CONCAT(TROMPELOEIL_INIT_WITH_STR,                                \
                     TROMPELOEIL_COUNT(__VA_ARGS__))(base, __VA_ARGS__)

#define TROMPELOEIL_PARAM_LIST15(func_type)                                    \
  TROMPELOEIL_PARAM_LIST14(func_type),                                         \
  ::trompeloeil::param_list_t<func_type, 14> p15

#define TROMPELOEIL_PARAM_LIST14(func_type)                                    \
  TROMPELOEIL_PARAM_LIST13(func_type),                                         \
  ::trompeloeil::param_list_t<func_type, 13> p14

#define TROMPELOEIL_PARAM_LIST13(func_type)                                    \
  TROMPELOEIL_PARAM_LIST12(func_type),                                         \
  ::trompeloeil::param_list_t<func_type, 12> p13

#define TROMPELOEIL_PARAM_LIST12(func_type)                                    \
  TROMPELOEIL_PARAM_LIST11(func_type),                                         \
  ::trompeloeil::param_list_t<func_type, 11> p12

#define TROMPELOEIL_PARAM_LIST11(func_type)                                    \
  TROMPELOEIL_PARAM_LIST10(func_type),                                         \
  ::trompeloeil::param_list_t<func_type, 10> p11

#define TROMPELOEIL_PARAM_LIST10(func_type)                                    \
  TROMPELOEIL_PARAM_LIST9(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 9> p10

#define TROMPELOEIL_PARAM_LIST9(func_type)                                     \
  TROMPELOEIL_PARAM_LIST8(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 8> p9

#define TROMPELOEIL_PARAM_LIST8(func_type)                                     \
  TROMPELOEIL_PARAM_LIST7(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 7> p8

#define TROMPELOEIL_PARAM_LIST7(func_type)                                     \
  TROMPELOEIL_PARAM_LIST6(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 6> p7

#define TROMPELOEIL_PARAM_LIST6(func_type)                                     \
  TROMPELOEIL_PARAM_LIST5(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 5> p6

#define TROMPELOEIL_PARAM_LIST5(func_type)                                     \
  TROMPELOEIL_PARAM_LIST4(func_type),                                          \
    ::trompeloeil::param_list_t<func_type, 4> p5


#define TROMPELOEIL_PARAM_LIST4(func_type)                                     \
  TROMPELOEIL_PARAM_LIST3(func_type),                                          \
    ::trompeloeil::param_list_t<func_type, 3> p4

#define TROMPELOEIL_PARAM_LIST3(func_type)                                     \
  TROMPELOEIL_PARAM_LIST2(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 2> p3

#define TROMPELOEIL_PARAM_LIST2(func_type)                                     \
  TROMPELOEIL_PARAM_LIST1(func_type),                                          \
  ::trompeloeil::param_list_t<func_type, 1> p2

#define TROMPELOEIL_PARAM_LIST1(func_type)                                     \
  ::trompeloeil::param_list_t<func_type, 0> p1

#define TROMPELOEIL_PARAM_LIST0(func_type)

#define TROMPELOEIL_PARAM_LIST(num, func_type)                                 \
  TROMPELOEIL_CONCAT(TROMPELOEIL_PARAM_LIST, num)(func_type)


#define TROMPELOEIL_PARAMS15 TROMPELOEIL_PARAMS14, p15
#define TROMPELOEIL_PARAMS14 TROMPELOEIL_PARAMS13, p14
#define TROMPELOEIL_PARAMS13 TROMPELOEIL_PARAMS12, p13
#define TROMPELOEIL_PARAMS12 TROMPELOEIL_PARAMS11, p12
#define TROMPELOEIL_PARAMS11 TROMPELOEIL_PARAMS10, p11
#define TROMPELOEIL_PARAMS10 TROMPELOEIL_PARAMS9,  p10
#define TROMPELOEIL_PARAMS9  TROMPELOEIL_PARAMS8,  p9
#define TROMPELOEIL_PARAMS8  TROMPELOEIL_PARAMS7,  p8
#define TROMPELOEIL_PARAMS7  TROMPELOEIL_PARAMS6,  p7
#define TROMPELOEIL_PARAMS6  TROMPELOEIL_PARAMS5,  p6
#define TROMPELOEIL_PARAMS5  TROMPELOEIL_PARAMS4,  p5
#define TROMPELOEIL_PARAMS4  TROMPELOEIL_PARAMS3,  p4
#define TROMPELOEIL_PARAMS3  TROMPELOEIL_PARAMS2,  p3
#define TROMPELOEIL_PARAMS2  TROMPELOEIL_PARAMS1,  p2
#define TROMPELOEIL_PARAMS1  ,                     p1
#define TROMPELOEIL_PARAMS0

#define TROMPELOEIL_PARAMS(num) TROMPELOEIL_CONCAT(TROMPELOEIL_PARAMS, num)

namespace trompeloeil
{
  class specialized;

  template <typename T = void>
  std::unique_lock<std::recursive_mutex> get_lock()
  {
    static std::recursive_mutex lock;
    return std::unique_lock<std::recursive_mutex>{ lock };
  }

  template <size_t N, typename T, bool legal = (N < std::tuple_size<T>::value)>
  struct conditional_tuple_element
  {
    using type = typename std::tuple_element<N, T>::type;
  };
  template <size_t N, typename T>
  struct conditional_tuple_element<N, T, false>
  {
    using type = int;
  };
  template <typename T>
  struct param_list;

  template <typename R, typename ... P>
  struct param_list<R(P...)>
  {
    using param_tuple = std::tuple<P...>;
    static size_t const size = std::tuple_size<param_tuple>::value;
    template <size_t N>
    using type = typename conditional_tuple_element<N, param_tuple>::type;
  };

  template <typename Sig, size_t N>
  using param_list_t = typename param_list<Sig>::template type<N>;

  class expectation_violation : public std::logic_error
  {
  public:
    using std::logic_error::logic_error;
  };

  struct location
  {
    location()
    noexcept
      : file("")
      , line(0U)
    {}

    location(
      char const* file_,
      unsigned long line_
    )
    noexcept
      : file{file_}
      , line{line_}
    {}

    char const *file;
    unsigned long line;
  };

  inline
  std::ostream&
  operator<<(
    std::ostream& os,
    const location& loc)
  {
    if (loc.line != 0U) os << loc.file << ':' << loc.line;
    return os;
  }

  enum class severity { fatal, nonfatal };

  using reporter_func = std::function<void(severity,
                                           char const *file,
                                           unsigned long line,
                                           std::string const &msg)>;

  inline
  void default_reporter(
    severity,
    char const *file,
    unsigned long line,
    std::string const &msg)
  {
    if (!std::current_exception())
    {
      std::stringstream os;
      os << location{ file, line } << "\n" << msg;
      throw expectation_violation(os.str());
    }
  }

  inline
  reporter_func&
  reporter_obj()
  {
    static reporter_func obj = default_reporter;
    return obj;
  }

  inline
  reporter_func set_reporter(
    reporter_func f)
  {
    return std::exchange(reporter_obj(), std::move(f));
  }

  class tracer;

  inline
  tracer*&
  tracer_obj()
    noexcept
  {
    static tracer* ptr = nullptr;
    return ptr;
  }

  inline
  tracer*
  set_tracer(
    tracer* obj)
  noexcept
  {
    auto& ptr = tracer_obj();
    auto rv = ptr;
    ptr = obj;
    return rv;
  }

  class tracer
  {
  public:
    virtual
    void
    trace(
      char const *file,
      unsigned long line,
      std::string const &call) = 0;
  protected:
    tracer()
    noexcept
      : previous{set_tracer(this)} {}
    tracer(tracer const&) = delete;
    tracer& operator=(tracer const&) = delete;
    virtual
    ~tracer()
    {
      set_tracer(previous);
    }
  private:
    tracer* previous = nullptr;
  };

  class stream_tracer : public tracer
  {
  public:
    stream_tracer(
      std::ostream& stream_)
      : stream(stream_) {}
    void
    trace(
      char const *file,
      unsigned long line,
      std::string const &call)
      override
    {
      stream << location{file, line} << '\n' << call << '\n';
    }
  private:
    std::ostream& stream;
  };

  template <typename T>
  struct reporter;

  template <typename T>
  void
  send_report(
    severity s,
    location loc,
    std::string const &msg)
  {
    reporter<T>::send(s, loc.file, loc.line, msg.c_str());
  }

  template <typename T>
  struct reporter
  {
    static
    void
    send(
      severity s,
      char const *file,
      unsigned long line,
      char const *msg);
  };

  template <typename T>
  void reporter<T>::
    send(
      severity s,
      char const *file,
      unsigned long line,
      char const *msg)
    {
      reporter_obj()(s, file, line, msg);
    }

  template <typename ... T>
  inline
  constexpr
  bool
  ignore(
    T const& ...)
  noexcept
  {
    return true;
  }

  struct matcher { };

  inline constexpr std::false_type is_matcher_(...) { return {}; }

  inline constexpr std::true_type is_matcher_(matcher const*) { return {}; }

  template <typename T>
  using is_matcher = decltype(::trompeloeil::is_matcher_(static_cast<std::decay_t<T>*>(nullptr)));

  template <typename T>
  struct typed_matcher : matcher
  {
    operator T() const;
  };

  template <>
  struct typed_matcher<std::nullptr_t> : matcher
  {
    template <typename T, typename = decltype(std::declval<T>() == nullptr)>
    operator T&&() const;

    template <typename T,
              typename = decltype(std::declval<T>() == nullptr),
              typename = std::enable_if_t<std::is_copy_constructible<T>::value>>
    operator T&()const;

    template <typename T, typename C>
    operator T C::*() const;
  };

  template <typename T, typename Pred>
  class duck_typed_matcher : public matcher
  {
  public:
    template <typename V,
              typename = decltype(std::declval<Pred>()(std::declval<V&&>(), std::declval<T>()))>
    operator V&&() const;

    template <typename V,
              typename = decltype(std::declval<Pred>()(std::declval<V&>(), std::declval<T>()))>
    operator V&() const;
  };

  constexpr inline std::false_type is_output_streamable_(...) { return {}; }

  template <typename T>
  constexpr
  inline
  auto
  is_output_streamable_(
    T*)
  -> decltype((std::declval<std::ostream&>() << std::declval<T&>()),std::true_type{})
  {
    return {};
  }

  template <typename T>
  inline
  constexpr
  auto
  is_output_streamable()
  {
    return is_output_streamable_(static_cast<T*>(nullptr));
  }

  struct stream_sentry
  {
    stream_sentry(
      std::ostream& os_)
      : os(os_)
      , width(os.width(0))
      , flags(os.flags(std::ios_base::dec | std::ios_base::left))
      , fill(os.fill(' '))
      {  }
    ~stream_sentry()
    {
      os.flags(flags);
      os.fill(fill);
      os.width(width);
    }
  private:
    std::ostream& os;
    std::streamsize width;
    std::ios_base::fmtflags flags;
    char fill;
  };


  template <typename T>
  struct is_null_comparable
  {
    template <typename U>
    static auto func(...)
      -> std::false_type;

    template <typename U>
    static auto func(U* u)
      -> std::integral_constant<decltype(*u == nullptr), !is_matcher<U>::value>;

    using type = decltype(func<T>(nullptr));
    static constexpr type value = {};
  };

  template <typename T>
  inline
  constexpr
  bool
  is_null(
    T const &t,
    std::true_type)
  noexcept(noexcept(std::declval<T>() == nullptr))
  {
    return t == nullptr;
  }

  template <typename T>
  inline
  constexpr
  bool
  is_null(
    T const &,
    std::false_type)
  noexcept
  {
    return false;
  }

  template <typename T>
  inline
  constexpr
  bool
  is_null(
    T const &t)
  {
    return ::trompeloeil::is_null(t,
                                  ::trompeloeil::is_null_comparable<T>::value);
  }

  template <typename T, bool = is_output_streamable<T>()>
  struct streamer
  {
    static
    void
    print(
      std::ostream& os,
      T const &t)
    {
      stream_sentry s(os);
      os << t;
    }
  };


  template <typename T>
  struct streamer<T, false>
  {
    static
    void
    print(
      std::ostream& os,
      T const &t)
    {
      stream_sentry s(os);
      static const char *linebreak = "\n";
      os << sizeof(T) << "-byte object={";
      os << (linebreak + (sizeof(T) <= 8)); // stupid construction silences VS2015 warining
      os << std::setfill('0') << std::hex;
      auto p = reinterpret_cast<uint8_t const*>(&t);
      for (size_t i = 0; i < sizeof(T); ++i)
      {
        os << " 0x" << std::setw(2) << unsigned(p[i]);
        if ((i & 0xf) == 0xf) os << '\n';
      }
      os << " }";
    }
  };

  template <typename T>
  void
  print(
    std::ostream& os,
    T const &t)
  {
    if (is_null(t))
    {
      os << "nullptr";
    }
    else
    {
      streamer<T>::print(os, t);
    }
  }

  inline
  constexpr
  auto
  param_compare_operator(
    ...)
  {
    return " == ";
  }

  inline
  constexpr
  auto
  param_compare_operator(
    matcher const*)
  {
    return "";
  }

  template <typename T>
  void
  print_expectation(
    std::ostream& os,
    T const& t)
  {
    os << param_compare_operator(&t);
    print(os, t);
    os << '\n';
  }

  template <typename T>
  class list_elem
  {
  public:
    list_elem(list_elem const&) = delete;
    list_elem& operator=(list_elem const&) = delete;
    list_elem(
      list_elem &&r)
    noexcept
      : next(r.next)
      , prev(&r)
    {
      r.invariant_check();

      next->prev = this;
      r.next = this;

      TROMPELOEIL_ASSERT(next->prev == this);
      TROMPELOEIL_ASSERT(prev->next == this);

      r.unlink();

      TROMPELOEIL_ASSERT(!r.is_linked());
      invariant_check();
    }
    virtual
    ~list_elem()
    {
      unlink();
    }
    void
    unlink()
    noexcept
    {
      invariant_check();
      auto n = next;
      auto p = prev;
      n->prev = p;
      p->next = n;
      next = this;
      prev = this;
      invariant_check();
    }
    void
    invariant_check()
    const
    noexcept
    {
#ifdef TROMPELOEIL_SANITY_CHECKS
      TROMPELOEIL_ASSERT(next->prev == this);
      TROMPELOEIL_ASSERT(prev->next == this);
      TROMPELOEIL_ASSERT((next == this) == (prev == this));
      TROMPELOEIL_ASSERT((prev->next == next) == (next == this));
      TROMPELOEIL_ASSERT((next->prev == prev) == (prev == this));
      auto pp = prev;
      auto nn = next;
      do {
        TROMPELOEIL_ASSERT((nn == this) == (pp == this));
        TROMPELOEIL_ASSERT(nn->next->prev == nn);
        TROMPELOEIL_ASSERT(nn->prev->next == nn);
        TROMPELOEIL_ASSERT(pp->next->prev == pp);
        TROMPELOEIL_ASSERT(pp->prev->next == pp);
        TROMPELOEIL_ASSERT((nn->next == nn) == (nn == this));
        TROMPELOEIL_ASSERT((pp->prev == pp) == (pp == this));
        nn = nn->next;
        pp = pp->prev;
      } while (nn != this);
#endif
    }
    bool
    is_linked()
    const
    noexcept
    {
      invariant_check();
      return next != this;
    }
  protected:
    list_elem() noexcept = default;
  public:
    list_elem* next = this;
    list_elem* prev = this;
  };

  class ignore_disposer
  {
  protected:
    template <typename T>
    TROMPELOEIL_NORETURN
    void
    dispose(
      T*)
    const
    noexcept
    {
      std::abort(); // must never be called
    }
  };

  class delete_disposer
  {
  protected:
    template <typename T>
    void
    dispose(
      T* t)
    const
    {
      delete t;
    }
  };

  template <typename T, typename Disposer = ignore_disposer>
  class list : private list_elem<T>, private Disposer
  {
  public:
    ~list();
    class iterator;
    iterator begin() const noexcept;
    iterator end() const noexcept;
    iterator push_front(T* t) noexcept;
    iterator push_back(T* t) noexcept;
    bool empty() const noexcept { return begin() == end(); }
  private:
    using list_elem<T>::invariant_check;
    using list_elem<T>::next;
    using list_elem<T>::prev;
  };

  template <typename T, typename Disposer>
  class list<T, Disposer>::iterator
    : public std::iterator<std::bidirectional_iterator_tag, T>
  {
    friend class list<T, Disposer>;
  public:
    iterator()
    noexcept
      : p{nullptr}
    {}
    friend
    bool
    operator==(
      iterator const &lh,
      iterator const &rh)
    noexcept
    {
      return lh.p == rh.p;
    }
    friend
    bool
    operator!=(
      iterator const &lh,
      iterator const &rh)
    noexcept
    {
      return !(lh == rh);
    }

    iterator&
    operator++()
    noexcept
    {
      p = p->next;
      return *this;
    }

    iterator
    operator++(int)
    noexcept
    {
      auto rv = *this;
      operator++();
      return rv;
    }
    T&
    operator*()
    noexcept
    {
      return static_cast<T&>(*p);
    }

    T*
    operator->()
    noexcept
    {
      return static_cast<T*>(p);
    }

  private:
    iterator(
      list_elem<T> const *t)
    noexcept
    : p{const_cast<list_elem<T>*>(t)}
    {}

    list_elem<T>* p;
  };

  template <typename T, typename Disposer>
  list<T, Disposer>::~list()
  {
    auto i = this->begin();
    while (i != this->end())
    {
      auto p = i++;
      Disposer::dispose(&*p);
    }
  }

  template <typename T, typename Disposer>
  auto
  list<T, Disposer>::begin()
  const
  noexcept
  -> iterator
  {
    return {next};
  }

  template <typename T, typename Disposer>
  auto
  list<T, Disposer>::end()
  const
  noexcept
  -> iterator
  {
    return {this};
  }

  template <typename T, typename Disposer>
  auto
  list<T, Disposer>::push_front(
    T* t)
  noexcept
  -> iterator
  {
    invariant_check();
    t->next = next;
    t->prev = this;
    next->prev = t;
    next = t;
    invariant_check();
    return {t};
  }

  template <typename T, typename Disposer>
  auto
  list<T, Disposer>::push_back(
    T* t)
  noexcept
  -> iterator
  {
    invariant_check();
    t->prev = prev;
    t->next = this;
    prev->next = t;
    prev = t;
    invariant_check();
    return {t};
  }

  class sequence_matcher;

  class sequence
  {
  public:
    sequence() noexcept = default;
    sequence(sequence&&) = delete;
    ~sequence();

    bool
    is_first(
      sequence_matcher const *m)
    const
    noexcept;

    void
    add_last(
      sequence_matcher *m)
    noexcept;

    void
    validate_match(
      severity s,
      sequence_matcher const *matcher,
      char const *seq_name,
      char const *match_name,
      location loc)
    const;

  private:
    list<sequence_matcher> matchers;
  };

  class sequence_matcher : public list_elem<sequence_matcher>
  {
  public:
    using init_type = std::pair<char const*, sequence&>;
    sequence_matcher(
      char const *exp,
      location loc,
      init_type i)
    noexcept
    : seq_name(i.first)
    , exp_name(exp)
    , exp_loc(loc)
    , seq(i.second)
    {
      seq.add_last(this);
    }
    void
    validate_match(
      severity s,
      char const *match_name,
      location loc)
    const
    {
      seq.validate_match(s, this, seq_name, match_name, loc);
    }
    bool
    is_first()
    const
    noexcept
    {
      return seq.is_first(this);
    }

    void
    retire()
    noexcept
    {
      this->unlink();
    }

    void
    print_expectation(std::ostream& os)
    const
    {
      os << exp_name << " at " << exp_loc;
    }

    char const*
    sequence_name()
    noexcept
    {
      return seq_name;
    }
  private:
    char const *seq_name;
    char const *exp_name;
    location    exp_loc;
    sequence&   seq;
  };

  inline
  bool
  sequence::is_first(
    sequence_matcher const *m)
  const
  noexcept
  {
    return !matchers.empty() && &*matchers.begin() == m;
  }

  inline
  void
  sequence::validate_match(
    severity s,
    sequence_matcher const *matcher,
    char const* seq_name,
    char const* match_name,
    location loc)
  const
  {
    if (is_first(matcher)) return;
    for (auto& m : matchers)
    {
      std::ostringstream os;
      os << "Sequence mismatch for sequence \"" << seq_name
         << "\" with matching call of " << match_name
         << " at " << loc
         << ". Sequence \"" << seq_name << "\" has ";
      m.print_expectation(os);
      os << " first in line\n";
      send_report<specialized>(s, loc, os.str());
    }
  }

  inline
  sequence::~sequence()
  {
    bool touched = false;
    std::ostringstream os;
    while (!matchers.empty())
    {
      auto m = matchers.begin();
      if (!touched)
      {
        os << "Sequence expectations not met at destruction of sequence object \""
           << m->sequence_name() << "\":";
        touched = true;
      }
      os << "\n  missing ";
      m->print_expectation(os);
      m->unlink();
    }
    if (touched)
    {
      os << "\n";
      send_report<specialized>(severity::nonfatal, location{}, os.str());
    }
  }

  inline
  void
  sequence::add_last(
    sequence_matcher *m)
  noexcept
  {
    matchers.push_back(m);
  }

  struct wildcard : public matcher
  {
    // This abomination of constructor seems necessary for g++ 4.9 and 5.1
    template <typename ... T>
    constexpr
    wildcard(
      T&& ...)
    noexcept
    {}

    template<typename T,
             typename = std::enable_if_t<!std::is_lvalue_reference<T>::value>>
    operator T&&()
    const;

    template<typename T,
             typename = std::enable_if_t<std::is_copy_constructible<T>::value
                                         || !std::is_move_constructible<T>::value>>
    operator T&()
    const;

    template <typename T>
    constexpr
    bool
    matches(
      T const&)
    const
    noexcept
    {
      return true;
    }

    friend
    std::ostream&
    operator<<(
      std::ostream& os,
      wildcard const&)
    noexcept
    {
      return os << " matching _";
    }
  };


  static constexpr wildcard const _{};

  template <typename T>
  struct typed_wildcard : public typed_matcher<T>
  {
    typed_wildcard(
      char const* t)
    : type(t)
    {
    }
    template <typename U>
    constexpr
    std::enable_if_t<std::is_same<typename std::decay<T>::type,
                                  typename std::decay<U>::type>::value,
                     bool>
    matches(
      U const &)
    const
    noexcept
    {
      return true;
    }
    friend
    std::ostream&
    operator<<(
      std::ostream& os,
      typed_wildcard<T> const& t)
    noexcept
    {
      return os << " matching ANY(" << t.type << ')';
    }
    char const* type;
  };

  template <typename T>
  void can_match_parameter(T&);

  template <typename T>
  void can_match_parameter(T&&);

  template <typename M>
  class ptr_deref : public matcher
  {
  public:
    template <typename U,
              typename = decltype(can_match_parameter<std::remove_reference_t<decltype(*std::declval<U>())>>(std::declval<M>()))>
    operator U() const;

    template <typename U>
    explicit
    ptr_deref(
      U&& m_)
      : m( std::forward<U>(m_) )
    {}

    template <typename U>
    bool
    matches(
      const U& u)
    const
    noexcept(noexcept(std::declval<M>().matches(*u)))
    {
      return (u != nullptr) && m.matches(*u);
    }

    friend
    std::ostream&
    operator<<(
      std::ostream& os,
      ptr_deref<M> const& p)
    {
      return os << p.m;
    }
  private:
    M m;
  };

  template <typename ActualType, typename MatchType, typename Predicate>
  struct matcher_kind
  {
    using type = typed_matcher<MatchType>;
  };

  template <typename ActualType, typename Predicate>
  struct matcher_kind<ActualType, wildcard, Predicate>
  {
    using type = duck_typed_matcher<ActualType, Predicate>;
  };

  template <typename ActualType, typename MatchType, typename Predicate>
  using matcher_kind_t =
    typename matcher_kind<ActualType, MatchType, Predicate>::type;

  template <typename Predicate, typename MatcherType, typename T>
  class predicate_matcher : private Predicate, public MatcherType
  {
  public:
    constexpr
    predicate_matcher(
      T v,
      Predicate pred,
      char const* op_string)
    noexcept(noexcept(T(std::declval<T&&>())) && noexcept(Predicate(std::declval<Predicate>())))
      : Predicate(pred)
      , value(std::move(v))
      , operator_string(op_string)
    {}
    template <typename V>
    constexpr
    bool
    matches(
      V&& v)
      const
      noexcept(noexcept(std::declval<Predicate const&>()(std::declval<V>(), std::declval<T>())))
    {
      return Predicate::operator()(v, value);
    }

    friend
    std::ostream&
    operator<<(
      std::ostream& os,
      predicate_matcher const& v)
    {
      os << v.operator_string;
      print(os, v.value);
      return os;
    }
  private:
    T value;
    char const* operator_string;
  };

  namespace lambdas {
    inline auto equal()
    {
      return [](auto x, auto y) -> decltype(x == y) { return x == y; };
    }
    inline auto not_equal()
    {
      return [](auto x, auto y) -> decltype(x != y) { return x != y; };
    }
    inline auto less()
    {
      return [](auto x, auto y) -> decltype(x < y) { return x < y; };
    }
    inline auto less_equal()
    {
      return [](auto x, auto y) -> decltype(x <= y) { return x <= y; };
    }
    inline auto greater()
    {
      return [](auto x, auto y) -> decltype(x > y) { return x > y; };
    }
    inline auto greater_equal()
    {
      return [](auto x, auto y) -> decltype(x >= y) { return x >= y; };
    }
  }
  template <typename MatchType, typename Predicate, typename T>
  inline
  predicate_matcher <Predicate, matcher_kind_t<T, MatchType, Predicate>, T>
  make_matcher(Predicate pred, char const *op_string, T t)
  {
    return {t, pred, op_string};
  }

  template <typename T = wildcard, typename V>
  inline
  auto
  eq(
    V v)
  {
    return make_matcher<T>(lambdas::equal(),
                           " == ",
                           v);
  }
  template <typename  T = wildcard, typename V>
  inline
  auto
  ne(
    V v)
  {
    return make_matcher<T>(lambdas::not_equal(),
                           " != ",
                           v);
  }


  template <typename T = wildcard, typename V>
  inline
  auto
  ge(
    V v)
  {
    return make_matcher<T>(lambdas::greater_equal(),
                           " >= ",
                           v);
  }

  template <typename T = wildcard, typename V>
  inline
  auto
  gt(
    V v)
  {
    return make_matcher<T>(lambdas::greater(),
                           " > ",
                           v);
  }

  template <typename T = wildcard, typename V>
  inline
  auto
  lt(
    V v)
  {
    return make_matcher<T>(lambdas::less(),
                           " < ",
                           v);
  }

  template <typename T = wildcard, typename V>
  inline
  auto
  le(
    V v)
  {
    return make_matcher<T>(lambdas::less_equal(),
                           " <= ",
                           v);
  }

  class re_base
  {
  public:
    re_base(
      std::string s)
      : re_s(std::move(s))
      , re(re_s)
    {}
    re_base(
      std::string s,
      std::regex_constants::syntax_option_type opt)
      : re_s(std::move(s))
      , re(re_s, opt)
    {}
    re_base(
      std::string s,
      std::regex_constants::match_flag_type flags)
      : re_s(std::move(s))
      , re(re_s), re_flags{flags}
    {}
    re_base(
      std::string s,
      std::regex_constants::syntax_option_type opt,
      std::regex_constants::match_flag_type flags)
      : re_s(std::move(s))
      , re(re_s, opt)
      , re_flags{flags}
    {}

    template <typename T>
    bool
    matches(
      T const& v)
    const
    {
      return !trompeloeil::is_null(v) && std::regex_search(v, re, re_flags);
    }

    friend
    std::ostream&
    operator<<(
      std::ostream& os,
      re_base const& m)
    {
      return os << " matching regular expression /" << m.re_s << '/';
    }

  private:
    using match_flag_type = std::regex_constants::match_flag_type;
    std::string re_s;
    std::regex re;
    match_flag_type re_flags = std::regex_constants::match_default;
  };

  template <typename T>
  class re_t : public re_base, public typed_matcher<T>
  {
  public:
    using re_base::re_base;
  };

  template <>
  class re_t<wildcard> : public re_base, public matcher
  {
  public:
    using re_base::re_base;
    template <typename T,
              typename = decltype(std::regex_search(std::declval<T&>(),
                                                    std::declval<std::regex>()))>
    operator T&() const;

    template <typename T,
              typename = decltype(std::regex_search(std::declval<T&&>(),
                                                    std::declval<std::regex>()))>
    operator T&&() const;

  };

  template <typename ... T>
  inline
  auto
  re(
    T&& ... t)
  -> decltype(::trompeloeil::re_t<wildcard>{std::forward<T>(t)...})
  {
    return {std::forward<T>(t)...};
  }

  template <typename Type, typename ... T>
  inline
  auto
  re(
    T&& ... t)
  -> decltype(::trompeloeil::re_t<Type>{std::forward<T>(t)...})
  {
    return {std::forward<T>(t)...};
  }

  template <typename T>
  std::string
  param_name_prefix(
    const T*)
  {
    return "";
  }

  template <typename M>
  std::string
  param_name_prefix(
    const ptr_deref<M>*)
  {
    return "*" + ::trompeloeil::param_name_prefix(static_cast<M*>(nullptr));
  }


  template <typename T>
  struct null_on_move
  {
  public:
    null_on_move()
    noexcept
      : p{nullptr}
    {}

    null_on_move(
      T* p_)
    noexcept
      : p{p_}
    {}

    null_on_move(
      null_on_move&&)
    noexcept
      : p{nullptr}
    {}

    null_on_move(
      null_on_move const&)
    noexcept
      : p{nullptr}
    {}

    null_on_move&
    operator=(
      const null_on_move&)
    noexcept
    {
      p = nullptr;
      return *this;
    }

    null_on_move&
    operator=(
      null_on_move&&)
    noexcept
    {
      p = nullptr;
      return *this;
    }

    null_on_move&
    operator=(
      T* t)
    noexcept
    {
      p = t;
      return *this;
    }

    T*&
    leak()
    noexcept
    {
      return p;
    }

    T&
    operator*()
    const
    noexcept
    {
      return *p;
    }

    T*
    operator->()
    const
    noexcept
    {
      return p;
    }

    explicit
    operator bool()
    const
    noexcept
    {
      return p != nullptr;
    }
  private:
    T* p;
  };

  struct sequence_handler_base
  {
    virtual
    ~sequence_handler_base()
    noexcept = default;

    virtual
    void
      validate(severity s, char const *, location) = 0;

    virtual
    bool
      is_first()
      const
      noexcept = 0;

    virtual
    void
      retire()
      noexcept = 0;
  };

  template <size_t N>
  struct sequence_handler : public sequence_handler_base
  {
  public:
    template <typename ... S>
    sequence_handler(
      char const *name,
      location loc,
      S&& ... s)
    noexcept
      : matchers{{name, loc, std::forward<S>(s)}...}
    {
    }

    void
    validate(
      severity s,
      char const *match_name,
      location loc)
    override
    {
      for (auto& e : matchers)
      {
        e.validate_match(s, match_name, loc);
      }
    }
    bool
    is_first()
    const
    noexcept
    override
    {
      // std::all_of() is almost always preferable. The only reason
      // for using a hand rolled loop is because it cuts compilation
      // times quite noticeably (almost 10% with g++5.1)
      for (auto& m : matchers)
      {
        if (!m.is_first()) return false;
      }
      return true;
    }
    void
    retire()
    noexcept
    override
    {
      for (auto& e : matchers)
      {
        e.retire();
      }
    }
  private:
    sequence_matcher matchers[N];
  };

  struct lifetime_monitor;

  template <typename T>
  class deathwatched : public T
  {
    static_assert(std::has_virtual_destructor<T>::value,
                  "virtual destructor is a necessity for deathwatched to work");
  public:
    template <typename ... U,
              typename = std::enable_if_t<std::is_constructible<T,U...>::value>>
    deathwatched(
      U&& ...u)
    noexcept(noexcept(T(std::declval<U>()...)))
      : T(std::forward<U>(u)...)
    {}

    ~deathwatched();

    trompeloeil::lifetime_monitor*&
    trompeloeil_expect_death(
      trompeloeil::lifetime_monitor* monitor)
    const
    noexcept
    {
      auto lock = get_lock();
      trompeloeil_lifetime_monitor = monitor;
      return trompeloeil_lifetime_monitor.leak();
    }
  private:
    mutable null_on_move<trompeloeil::lifetime_monitor> trompeloeil_lifetime_monitor;
  };

  struct expectation {
    virtual ~expectation() = default;
  };

  struct lifetime_monitor : public expectation
  {
    template <typename T>
    lifetime_monitor(
      ::trompeloeil::deathwatched<T> const &obj,
      char const* obj_name_,
      char const* invocation_name_,
      char const* call_name_,
      location loc_)
    noexcept
      : object_monitor(obj.trompeloeil_expect_death(this))
      , loc(loc_)
      , object_name(obj_name_)
      , invocation_name(invocation_name_)
      , call_name(call_name_)
    {
    }
    lifetime_monitor(lifetime_monitor const&) = delete;
    ~lifetime_monitor()
    {
      auto lock = get_lock();
      if (!died)
      {
        std::ostringstream os;
        os << "Object " << object_name << " is still alive";
        send_report<specialized>(severity::nonfatal, loc, os.str());
        object_monitor = nullptr; // prevent its death poking this cadaver
      }
    }
    void
    notify()
    noexcept
    {
      died = true;
      if (sequences) sequences->validate(severity::nonfatal, call_name, loc);
    }
    template <typename ... T>
    void
    set_sequence(
      T&& ... t)
    {
      auto seq = new sequence_handler<sizeof...(T)>(invocation_name,
                                                    loc,
                                                    std::forward<T>(t)...);
      sequences.reset(seq);
    }
  private:
    bool               died = false;
    lifetime_monitor *&object_monitor;
    location           loc;
    char const        *object_name;
    char const        *invocation_name;
    char const        *call_name;
    std::unique_ptr<sequence_handler_base>  sequences;
  };

  template <typename T>
  deathwatched<T>::~deathwatched()
  {
    auto lock = get_lock();
    if (trompeloeil_lifetime_monitor)
    {
      trompeloeil_lifetime_monitor->notify();
      return;
    }
    std::ostringstream os;
    os << "Unexpected destruction of "
       << typeid(T).name() << "@" << this << '\n';
    send_report<specialized>(severity::nonfatal,
                             location{},
                             os.str());
  }

  template<typename T>
  struct return_of;

  template<typename R, typename ... A>
  struct return_of<R(A...)>
  {
    using type = R;
  };

  template<typename T>
  using return_of_t = typename return_of<T>::type;

  template<typename T>
  struct call_params_type;

  template<typename R, typename ... T>
  struct call_params_type<R(T...)>
  {
    using type = std::tuple<typename std::add_lvalue_reference<T>::type...>;
  };

  template<typename T>
  using call_params_type_t = typename call_params_type<T>::type;

  template <typename R>
  struct default_return_t
  {
    TROMPELOEIL_NORETURN static R value()
    {
      std::abort(); // must never be called
    }
  };

  template <>
  struct default_return_t<void>
  {
    // g++ 4.9 does not allow constexpr for void function
    static void value() {}
  };

  template <typename R>
  inline
  R
  default_return()
  {
    return default_return_t<R>::value();
  }


  template<typename Sig>
  struct call_matcher_base;

  template <typename Sig>
  struct call_matcher_list : public list<call_matcher_base<Sig>>
  {
    void decommission()
    {
      auto lock = get_lock();
      auto iter = this->begin();
      auto const e = this->end();
      while (iter != e)
      {
        auto i = iter++;
        auto &m = *i;
        m.mock_destroyed();
        m.unlink();
      }
    }
  };

  template<typename Sig>
  struct call_matcher_base : public list_elem<call_matcher_base<Sig> >
  {
    call_matcher_base() = default;
    call_matcher_base(call_matcher_base&&) = delete;

    virtual
    ~call_matcher_base() = default;

    virtual
    void
    mock_destroyed() = 0;

    virtual
    bool
    matches(
      call_params_type_t<Sig> const&)
    const = 0;

    virtual
    bool
    first_in_sequence()
    const
    noexcept = 0;

    virtual
    void
    log_call(
      tracer* obj,
      call_params_type_t<Sig>& p)
    const = 0;

    virtual
    void
    run_actions(
      call_params_type_t<Sig> &,
      call_matcher_list<Sig> &saturated_list
    ) = 0;

    virtual
    std::ostream&
    report_signature(
      std::ostream&)
    const = 0;

    TROMPELOEIL_NORETURN
    virtual
    std::ostream&
    report_mismatch(
      std::ostream&,
      call_params_type_t<Sig> const &) = 0;

    virtual
    return_of_t<Sig>
    return_value(
      call_params_type_t<Sig>& p) = 0;

    virtual
    void
    report_missed(
      char const *reason) = 0;
  };

  template <typename T, typename U>
  bool
  param_matches_impl(
    T const& t,
    U const& u,
    matcher const*)
  noexcept(noexcept(t.matches(u)))
  {
    return t.matches(u);
  }

  template <typename T, typename U>
  bool
  param_matches_impl(
    T const& t,
    U const& u,
    ...)
  noexcept(noexcept(t == u))
  {
    return t == u;
  }

  template <typename T, typename U>
  bool
  param_matches(
    T const& t,
    U const& u)
  noexcept(noexcept(param_matches_impl(t, u, &t)))
  {
    return ::trompeloeil::param_matches_impl(t, u, &t);
  }

  template <size_t ... I, typename T, typename U>
  bool
  match_parameters(
    std::index_sequence<I...>,
    T const& t,
    U const& u)
    noexcept(noexcept(std::initializer_list<bool>{trompeloeil::param_matches(std::get<I>(t),std::get<I>(u))...}))
  {
    bool all_true = true;
    ::trompeloeil::ignore(t, u); // Kills unmotivated VS2015 warning in the empty case
    ::trompeloeil::ignore(std::initializer_list<bool>{all_true = all_true && ::trompeloeil::param_matches(std::get<I>(t), std::get<I>(u))...});
    return all_true;
  }

  template <typename ... T, typename ... U>
  bool
  match_parameters(
    std::tuple<T...> const& t,
    std::tuple<U...> const& u)
  noexcept(noexcept(match_parameters(std::make_index_sequence<sizeof...(T)>{}, t, u)))
  {
    return ::trompeloeil::match_parameters(std::make_index_sequence<sizeof...(T)>{}, t, u);
  }

  template <typename V, typename P>
  void print_mismatch(
    std::ostream& os,
    size_t num,
    V const& v,
    P const& p)
  {
    if (!::trompeloeil::param_matches(v, p))
    {
      auto prefix = ::trompeloeil::param_name_prefix(&v) + "_";
      os << "  Expected " << std::setw((num < 9) + 1) << prefix << num+1;
      ::trompeloeil::print_expectation(os, v);
    }
  }

  template <typename ... V, typename ... P, size_t ... I>
  void print_mismatch(
    std::ostream& os,
    std::index_sequence<I...>,
    std::tuple<V...> const& v,
    std::tuple<P...> const& p)
  {
    ::trompeloeil::ignore(os, v, p);  // Kills unmotivated VS2015 warning in the empty case
    ::trompeloeil::ignore(std::initializer_list<int>{(print_mismatch(os, I, std::get<I>(v), std::get<I>(p)),0)...});
  }

  template <typename ... V, typename ... P>
  void print_mismatch(
    std::ostream& os,
    std::tuple<V...> const& v,
    std::tuple<P...> const& p)
  {
    print_mismatch(os, std::make_index_sequence<sizeof...(V)>{}, v, p);
  }

  template <typename T>
  void missed_value(
    std::ostream& os,
    int i,
    T const& t)
  {
    auto prefix = ::trompeloeil::param_name_prefix(&t) + "_";
    os << "  param " << std::setw((i < 9) + 1) << prefix << i + 1
       << ::trompeloeil::param_compare_operator(&t);
    ::trompeloeil::print(os, t);
    os << '\n';
  }

  template <size_t ... I, typename ... T>
  void missed_values(
    std::ostream& os,
    std::index_sequence<I...>,
    std::tuple<T...> const& t)
  {
    ::trompeloeil::ignore(os, t);  // Kills unmotivated VS2015 warning in the empty case
    ::trompeloeil::ignore(std::initializer_list<int>{(missed_value(os, I, std::get<I>(t)),0)...});
  }

  template <typename ... T>
  std::string
  missed_values(
  std::tuple<T...> const &t)
  {
    std::ostringstream os;
    missed_values(os, std::make_index_sequence<sizeof...(T)>{}, t);
    return os.str();
  }


  template <typename Sig>
  call_matcher_base <Sig> *
  find(
    call_matcher_list <Sig> &list,
    call_params_type_t <Sig> const &p)
  noexcept
  {
    call_matcher_base<Sig>* first_match = nullptr;
    for (auto& i : list)
    {
      if (i.matches(p))
      {
        if (i.first_in_sequence())
        {
          return &i;
        }
        if (!first_match)
        {
          first_match = &i;
        }
      }
    }
    return first_match;
  }

  template <typename Sig>
  TROMPELOEIL_NORETURN
  void
  report_mismatch(
    call_matcher_list <Sig> &matcher_list,
    call_matcher_list <Sig> &saturated_list,
    std::string const &name,
    call_params_type_t <Sig> const &p)
  {
    std::ostringstream os;
    os << "No match for call of " << name << " with.\n" << missed_values(p);
    bool saturated_match = false;
    for (auto& m : saturated_list)
    {
      if (m.matches(p))
      {
        if (!saturated_match)
        {
          os << "\nMatches saturated call requirement\n";
          saturated_match = true;
        }
        os << "  ";
        m.report_signature(os) << '\n';
      }
    }
    if (!saturated_match)
    {
      for (auto& m : matcher_list)
      {
        os << "\nTried ";
        m.report_mismatch(os, p);
      }
    }
    send_report<specialized>(severity::fatal, location{}, os.str());
    std::abort(); // must never get here.
  }

  template <typename Sig>
  class return_handler
  {
  public:
    virtual
    ~return_handler() = default;

    virtual
    return_of_t<Sig>
    call(
      call_params_type_t<Sig>& params) = 0;
  };

  template <typename Sig, typename T>
  class return_handler_t : public return_handler<Sig>
  {
  public:
    template <typename U>
    return_handler_t(
      U&& u)
    : func(std::forward<U>(u))
    {}

    return_of_t<Sig>
    call(
      call_params_type_t<Sig>& params)
    override
    {
      return func(params);
    }
  private:
    T func;
  };

  template<typename Sig>
  class condition_base : public list_elem<condition_base<Sig> >
  {
  public:
    condition_base(
      char const *n)
    noexcept
      : id(n)
    {}

    virtual
    ~condition_base() = default;

    virtual
    bool
    check(
      call_params_type_t<Sig> const&)
    const = 0;

    virtual
    char const*
    name()
    const
    noexcept
    {
      return id;
    }
  private:
    char const *id;
  };

  template <typename Sig>
  using condition_list = list<condition_base<Sig>, delete_disposer >;

  template<typename Sig, typename Cond>
  struct condition : public condition_base<Sig>
  {
    condition(
      char const *str_,
      Cond c_)
      : condition_base<Sig>(str_)
      , c(c_) {}

    bool
    check(
      call_params_type_t<Sig> const & t)
    const
    override
    {
      return c(t);
    }

  private:
    Cond c;
  };

  template<typename Sig>
  struct side_effect_base : public list_elem<side_effect_base<Sig> >
  {
    virtual
    ~side_effect_base() = default;

    virtual
    void
    action(
      call_params_type_t<Sig> &)
    const = 0;
  };

  template<typename Sig>
  using side_effect_list = list<side_effect_base<Sig>, delete_disposer>;

  template<typename Sig, typename Action>
  struct side_effect : public side_effect_base<Sig>
  {
    template <typename A>
    side_effect(
      A&& a_)
    : a(std::forward<A>(a_))
    {}

    void
    action(
      call_params_type_t<Sig> &t)
    const
    override
    {
      a(t);
    }
  private:
    Action a;
  };

  template <unsigned long long L, unsigned long long H = L>
  struct multiplicity { };

  template<typename R, typename Parent>
  struct return_injector : Parent
  {
    using return_type = R;
  };

  template <typename Parent>
  struct throw_injector : Parent
  {
    static bool const throws = true;
  };

  template <typename Parent>
  struct sideeffect_injector : Parent
  {
    static bool const side_effects = true;
  };

  template <typename Parent, unsigned long long H>
  struct call_limit_injector : Parent
  {
    static bool               const call_limit_set = true;
    static unsigned long long const upper_call_limit = H;
  };

  template <typename Parent>
  struct sequence_injector : Parent
  {
    static bool const sequence_set = true;
  };

  template <typename Matcher, typename modifier_tag, typename Parent>
  struct call_modifier : public Parent
  {
    using typename Parent::signature;
    using typename Parent::return_type;
    using Parent::call_limit_set;
    using Parent::upper_call_limit;
    using Parent::sequence_set;
    using Parent::throws;
    using Parent::side_effects;

    call_modifier(
       std::unique_ptr<Matcher>&& m)
    noexcept
      : matcher{std::move(m)}
    {}

    template <typename D>
    call_modifier&&
    with(
      char const* str,
      D&& d)
    &&
    {
      matcher->add_condition(str, std::forward<D>(d));
      return std::move(*this);
    }

    template <typename A>
    call_modifier<Matcher, modifier_tag, sideeffect_injector<Parent>>
    sideeffect(
      A&& a)
    {
      constexpr bool forbidden = upper_call_limit == 0U;
      static_assert(!forbidden,
                    "SIDE_EFFECT for forbidden call does not make sense");
      matcher->add_side_effect(std::forward<A>(a));
      return {std::move(matcher)};
    }

    template <typename H>
    call_modifier<Matcher, modifier_tag, return_injector<return_of_t<signature>, Parent >>
    handle_return(
      H&& h)
    {
      using params_type = call_params_type_t<signature>&;
      using sigret = return_of_t<signature>;
      using ret = decltype(std::declval<H>()(std::declval<params_type>()));
      // don't know why MS VS 2015 RC doesn't like std::result_of

      constexpr bool is_first_return   = std::is_same<return_type, void>::value;
      constexpr bool void_signature    = std::is_same<sigret, void>::value;
      constexpr bool matching_ret_type = std::is_constructible<sigret, ret>::value;

      static_assert(matching_ret_type || !void_signature,
                    "RETURN does not make sense for void-function");
      static_assert(matching_ret_type || void_signature,
                    "RETURN value is not convertible to the return type of the function");
      static_assert(is_first_return,
                    "Multiple RETURN does not make sense");
      static_assert(!throws || upper_call_limit == 0,
                    "THROW and RETURN does not make sense");
      static_assert(upper_call_limit > 0ULL,
                    "RETURN for forbidden call does not make sense");

      constexpr bool valid = matching_ret_type && is_first_return && !throws && upper_call_limit > 0ULL;
      using tag = std::integral_constant<bool, valid>;
      matcher->set_return(tag{}, std::forward<H>(h));
      return {std::move(matcher)};
    }

    template <typename H>
    call_modifier<Matcher, modifier_tag, throw_injector<Parent> >
    handle_throw(
      H&& h)
    {
      static_assert(!throws,
                    "Multiple THROW does not make sense");
      constexpr bool has_return = !std::is_same<return_type, void>::value;
      static_assert(!has_return,
                    "THROW and RETURN does not make sense");

      constexpr bool valid = !throws && !has_return;
      using tag = std::integral_constant<bool, valid>;
      auto handler = [=](auto& p) -> decltype(auto)
      {
        h(p);
        return trompeloeil::default_return<return_of_t<signature>>();
      };
      matcher->set_return(tag{}, std::move(handler));
      return {std::move(matcher)};
    }
    template <unsigned long long L,
              unsigned long long H,
              bool               times_set = call_limit_set>
    call_modifier<Matcher, modifier_tag, call_limit_injector<Parent, H>>
    times(
      multiplicity<L, H>)
    {
      static_assert(!times_set,
                    "Only one TIMES call limit is allowed, but it can express an interval");

      static_assert(H >= L,
                    "In TIMES the first value must not exceed the second");

      static_assert(H > 0 || !throws,
                    "THROW and TIMES(0) does not make sense");

      static_assert(H > 0 || std::is_same<return_type, void>::value,
                    "RETURN and TIMES(0) does not make sense");

      static_assert(H > 0 || !side_effects,
                    "SIDE_EFFECT and TIMES(0) does not make sense");

      matcher->min_calls = L;
      matcher->max_calls = H;
      return {std::move(matcher)};
    }

    template <typename ... T,
              bool b = sequence_set>
    call_modifier<Matcher, modifier_tag, sequence_injector<Parent>>
    in_sequence(
      T&& ... t)
    {
      static_assert(!b,
                    "Multiple IN_SEQUENCE does not make sense."
                    " You can list several sequence objects at once");

      matcher->set_sequence(std::forward<T>(t)...);
      return {std::move(matcher)};
    }
    std::unique_ptr<Matcher> matcher;
  };

  inline
  void
  report_unfulfilled(
    const char* reason,
    char const        *name,
    std::string const &values,
    unsigned long long min_calls,
    unsigned long long call_count,
    location           loc)
  {
    std::ostringstream os;
    os << reason
       << ":\nExpected " << name << " to be called ";
    if (min_calls == 1)
      os << "once";
    else
      os << min_calls << " times";
    os << ", actually ";
    switch (call_count)
    {
    case 0:
      os << "never called\n"; break;
    case 1:
      os << "called once\n"; break;
    default:
      os << "called " << call_count << " times\n";
    }
    os << values;
    send_report<specialized>(severity::nonfatal, loc, os.str());
  }

  inline
  void
  report_forbidden_call(
    char const *name,
    location loc,
    std::string const& values)
  {
    std::ostringstream os;
    os << "Match of forbidden call of " << name
       << " at " << loc << '\n' << values;
    send_report<specialized>(severity::fatal, loc, os.str());
  }

  template <typename Sig>
  struct matcher_info
  {
    using signature = Sig;
    using return_type = void;
    static unsigned long long const upper_call_limit = 1;
    static bool const throws = false;
    static bool const call_limit_set = false;
    static bool const sequence_set = false;
    static bool const side_effects = false;
  };


  template<typename Sig, typename Value>
  struct call_matcher : public call_matcher_base<Sig>, expectation
  {
    template<typename ... U>
    call_matcher(
      char const *file,
      unsigned long line,
      char const *call_string,
      U &&... u)
    : loc{file, line},
      name{call_string},
      val(std::forward<U>(u)...)
    {}

    call_matcher(call_matcher &&r) = delete;

    ~call_matcher()
    {
      auto lock = get_lock();
      if (is_unfulfilled())
      {
        report_missed("Unfulfilled expectation");
      }
      this->unlink();
    }

    bool
    is_unfulfilled()
    const
    noexcept
    {
      return !reported && this->is_linked() && call_count < min_calls;
    }

    void
    mock_destroyed()
    override
    {
      if (is_unfulfilled())
      {
        report_missed("Pending expectation on destroyed mock object");
      }
    }

    call_matcher*
    hook_last(
      call_matcher_list<Sig> &list)
    noexcept
    {
      list.push_front(this);
      return this;
    }

    bool
    matches(
      call_params_type_t<Sig> const& params)
    const
    override
    {
      return match_parameters(val, params) && match_conditions(params);
    }

    bool
    match_conditions(
      call_params_type_t<Sig> const & params)
    const
    {
      // std::all_of() is almost always preferable. The only reason
      // for using a hand rolled loop is because it cuts compilation
      // times quite noticeably (almost 10% with g++5.1)
      for (auto& c : conditions)
      {
        if (!c.check(params)) return false;
      }
      return true;
    }

    bool
    first_in_sequence()
    const
    noexcept
    override
    {
      auto saturated = call_count >= min_calls;
      return saturated || !sequences || sequences->is_first();
    }

    return_of_t<Sig>
    return_value(
      call_params_type_t<Sig>& params)
    override
    {
      if (!return_handler_obj) return default_return<return_of_t<Sig>>();
      return return_handler_obj->call(params);
    }

    void
    log_call(
      tracer* t_obj,
      call_params_type_t<Sig>& params
    )
    const
    override
    {
      std::ostringstream os;
      os << name << " with.\n" << missed_values(params);
      t_obj->trace(loc.file, loc.line, os.str());
    }

    void
    run_actions(
      call_params_type_t<Sig>& params,
      call_matcher_list<Sig> &saturated_list)
    override
    {
      if (call_count < min_calls && sequences)
      {
        sequences->validate(severity::fatal, name, loc);
      }
      if (max_calls == 0)
      {
        reported = true;
        report_forbidden_call(name, loc, missed_values(params));
      }
      if (++call_count == min_calls && sequences)
      {
        sequences->retire();
      }
      if (call_count == max_calls)
      {
        this->unlink();
        saturated_list.push_back(this);
      }
      for (auto& a : actions) a.action(params);
    }

    std::ostream&
    report_signature(
      std::ostream& os)
    const override
    {
      return os << name << " at " << loc;
    }

    std::ostream&
    report_mismatch(
      std::ostream& os,
      call_params_type_t<Sig> const & params)
    override
    {
      reported = true;
      report_signature(os);
      if (match_parameters(val, params))
      {
        for (auto& cond : conditions)
        {
          if (!cond.check(params))
          {
            os << "\n  Failed WITH(" << cond.name() << ')';
          }
        }
      }
      else
      {
        os << '\n';
        ::trompeloeil::print_mismatch(os, val, params);
      }
      return os;
    }

    void
    report_missed(
      char const *reason)
    override
    {
      reported = true;
      report_unfulfilled(
        reason,
        name,
        missed_values(val),
        min_calls,
        call_count,
        loc);
    }
    template <typename C>
    void
    add_condition(
      char const *str,
      C&& c)
    {
      auto cond = new condition<Sig, C>(str, std::forward<C>(c));
      conditions.push_back(cond);
    }

    template <typename S>
    void
    add_side_effect(
      S&& s)
    {
      auto effect = new side_effect<Sig, S>(std::forward<S>(s));
      actions.push_back(effect);
    }

    template <typename ... T>
    void
    set_sequence(
      T&& ... t)
    {
      auto seq = new sequence_handler<sizeof...(T)>(name,
                                                    loc,
                                                    std::forward<T>(t)...);
      sequences.reset(seq);
    }

    template <typename T>
    inline
    void
    set_return(
      std::true_type,
      T&& h)
    {
      using basic_t = typename std::remove_reference<T>::type;
      using handler = return_handler_t<Sig, basic_t>;
      return_handler_obj.reset(new handler(std::forward<T>(h)));
    }

    template <typename T>
    inline                           // Never called. Used to limit errmsg
    static                           // with RETURN of wrong type and after:
    void                             //   FORBIDDEN_CALL
    set_return(std::false_type, T&&) //   RETURN
      noexcept;                      //   THROW

    condition_list<Sig>                    conditions;
    side_effect_list<Sig>                  actions;
    std::unique_ptr<return_handler<Sig>>   return_handler_obj;
    std::unique_ptr<sequence_handler_base> sequences;
    location                               loc;
    char const                            *name;
    unsigned long long                     call_count = 0;
    unsigned long long                     min_calls = 1;
    unsigned long long                     max_calls = 1;
    Value                                  val;
    bool                                   reported = false;
  };


  template<int N, typename T>
  constexpr
  inline
  decltype(auto)
  arg(T* t, std::true_type)
  {
    return std::get<N-1>(*t);
  }

  template <int N>
  struct illegal_argument {
    illegal_argument(illegal_argument&&) = delete;
    illegal_argument operator&() const = delete;

    template <typename T>
    operator T()
    const
    {
      static_assert(!N, "illegal argument");
      return std::declval<T>();
    }
  };

  template <int N>
  inline
  illegal_argument<N>&
  arg(void const*, std::false_type)
    noexcept
  {
      static illegal_argument<N> v{};
      return v;
  }

  template <int N, typename T>
  decltype(auto)
  mkarg(
    T& t)
  noexcept
  {
    return arg<N>(&t, std::integral_constant<bool, (N <= std::tuple_size<T>::value)>{});
  }

  template <typename Mock>
  struct call_validator_t
  {
    template <typename M, typename Tag, typename Info>
    auto
    make_expectation(
      std::true_type,
      call_modifier<M, Tag, Info>&& m)
    const
    noexcept
    {
      auto lock = get_lock();
      m.matcher->hook_last(obj.trompeloeil_matcher_list(Tag{}));
      return std::move(m).matcher;
    }

    template <typename T>
    static                                           // Never called. Used to
    std::unique_ptr<expectation>                     // limit errmsg when RETURN
    make_expectation(std::false_type, T&&) noexcept; // is missing in non-void
                                                     // function

    template <typename M, typename Tag, typename Info>
    inline
    auto
    operator+(
      call_modifier<M, Tag, Info>&& t)
    const
    {
      using T = call_modifier<M, Tag, Info>;
      using sigret = return_of_t<typename T::signature>;
      using ret = typename T::return_type;
      constexpr bool retmatch = std::is_same<ret, sigret>::value;
      constexpr bool legal = T::throws || retmatch;
      static_assert(legal, "RETURN missing for non-void function");
      auto tag = std::integral_constant<bool, legal>{};
      return make_expectation(tag, std::move(t));
    }
    Mock& obj;
  };

  template <typename Mock>
  call_validator_t<Mock> call_validator(
    void const*,
    Mock& obj)
  {
    return {obj};
  }
  template <typename T,
            typename = std::enable_if_t<std::is_lvalue_reference<T&&>::value>>
  inline
  T&&
  decay_return_type(
    T&& t)
  {
    return std::forward<T>(t);
  }

  template <typename T,
            typename = std::enable_if_t<std::is_rvalue_reference<T&&>::value>>
  inline
  T
  decay_return_type(
    T&& t)
  {
    return std::forward<T>(t);
  }

  template <typename T, size_t N>
  inline
  T*
  decay_return_type(
    T (&t)[N])
  {
    return t;
  }

  template <bool sequence_set>
  struct lifetime_monitor_modifier
  {
    operator std::unique_ptr<lifetime_monitor>() { return std::move(monitor);}
    operator std::unique_ptr<expectation>() { return std::move(monitor);}
    template <typename ... T, bool b = sequence_set>
    lifetime_monitor_modifier<true>
    in_sequence(T&& ... t)
    {
      static_assert(!b,
                    "Multiple IN_SEQUENCE does not make sense."
                      " You can list several sequence objects at once");
      monitor->set_sequence(std::forward<T>(t)...);
      return { std::move(monitor) };
    }
    std::unique_ptr<lifetime_monitor> monitor;
  };

  template <typename Sig>
  struct expectations
  {
    ~expectations() {
      active.decommission();
      saturated.decommission();
    }
    call_matcher_list<Sig> active;
    call_matcher_list<Sig> saturated;
  };

  template <typename Sig, typename ... P>
  return_of_t<Sig> mock_func(std::false_type, P&& ...);


  template <typename Sig, typename ... P>
  return_of_t<Sig>
  mock_func(std::true_type,
            expectations<Sig>& e,
            char const *func_name,
            char const *sig_name,
            P&& ... p)
  {
    auto lock = get_lock();

    call_params_type_t<void(P...)> param_value(std::forward<P>(p)...);

    auto i = find(e.active, param_value);
    if (!i)
    {
      report_mismatch(e.active,
                      e.saturated,
                      func_name + std::string(" with signature ") + sig_name,
                      param_value);
    }
    if (auto t_obj = tracer_obj())
    {
      i->log_call(t_obj, param_value);
    }
    i->run_actions(param_value, e.saturated);
    return i->return_value(param_value);
  }
}

template <typename M,
          typename = std::enable_if_t<::trompeloeil::is_matcher<M>::value>>
inline
auto
operator*(
  M&& m)
{
  return ::trompeloeil::ptr_deref<std::decay_t<M>>{std::forward<M>(m)};
}

#define TROMPELOEIL_ID(name)                                             \
  TROMPELOEIL_CONCAT(trompeloeil_ ## name ## _, __LINE__)
#ifdef _MSC_VER
#define TROMPELOEIL_MAKE_MOCK0(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,0, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK1(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,1, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK2(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,2, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK3(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,3, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK4(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,4, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK5(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,5, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK6(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,6, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK7(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,7, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK8(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,8, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK9(name, sig, ...)                           \
  TROMPELOEIL_MAKE_MOCK_(name,,9, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK10(name, sig, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,,10, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK11(name, sig, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,,11, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK12(name, sig, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,,12, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK13(name, sig, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,,13, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK14(name, sig, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,,14, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK15(name, sig, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,,15, sig, __VA_ARGS__,,)

#define TROMPELOEIL_MAKE_CONST_MOCK0(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,0, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK1(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,1, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK2(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,2, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK3(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,3, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK4(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,4, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK5(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,5, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK6(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,6, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK7(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,7, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK8(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,8, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK9(name, sig, ...)                     \
  TROMPELOEIL_MAKE_MOCK_(name,const,9, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK10(name, sig, ...)                    \
  TROMPELOEIL_MAKE_MOCK_(name,const,10, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK11(name, sig, ...)                    \
  TROMPELOEIL_MAKE_MOCK_(name,const,11, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK12(name, sig, ...)                    \
  TROMPELOEIL_MAKE_MOCK_(name,const,12, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK13(name, sig, ...)                    \
  TROMPELOEIL_MAKE_MOCK_(name,const,13, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK14(name, sig, ...)                    \
  TROMPELOEIL_MAKE_MOCK_(name,const,14, sig, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK15(name, sig, ...)                    \
  TROMPELOEIL_MAKE_MOCK_(name,const,15, sig, __VA_ARGS__,,)


#else
// sane standards compliant preprocessor

#define TROMPELOEIL_MAKE_MOCK0(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,0, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK1(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,1, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK2(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,2, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK3(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,3, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK4(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,4, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK5(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,5, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK6(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,6, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK7(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,7, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK8(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,8, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK9(name, ...)                                \
  TROMPELOEIL_MAKE_MOCK_(name,,9, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK10(name, ...)                               \
  TROMPELOEIL_MAKE_MOCK_(name,,10, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK11(name, ...)                               \
  TROMPELOEIL_MAKE_MOCK_(name,,11, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK12(name, ...)                               \
  TROMPELOEIL_MAKE_MOCK_(name,,12, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK13(name, ...)                               \
  TROMPELOEIL_MAKE_MOCK_(name,,13, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK14(name, ...)                               \
  TROMPELOEIL_MAKE_MOCK_(name,,14,__VA_ARGS__,,)
#define TROMPELOEIL_MAKE_MOCK15(name, ...)                               \
  TROMPELOEIL_MAKE_MOCK_(name,,15, __VA_ARGS__,,)

#define TROMPELOEIL_MAKE_CONST_MOCK0(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,0, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK1(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,1, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK2(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,2, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK3(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,3, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK4(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,4, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK5(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,5, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK6(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,6, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK7(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,7, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK8(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,8, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK9(name, ...)                          \
  TROMPELOEIL_MAKE_MOCK_(name,const,9, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK10(name, ...)                         \
  TROMPELOEIL_MAKE_MOCK_(name,const,10, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK11(name, ...)                         \
  TROMPELOEIL_MAKE_MOCK_(name,const,11, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK12(name, ...)                         \
  TROMPELOEIL_MAKE_MOCK_(name,const,12, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK13(name, ...)                         \
  TROMPELOEIL_MAKE_MOCK_(name,const,13, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK14(name, ...)                         \
  TROMPELOEIL_MAKE_MOCK_(name,const,14, __VA_ARGS__,,)
#define TROMPELOEIL_MAKE_CONST_MOCK15(name, ...)                         \
  TROMPELOEIL_MAKE_MOCK_(name,const,15, __VA_ARGS__,,)

#endif



#define TROMPELOEIL_MAKE_MOCK_(name, constness, num, sig, spec, ...)           \
  using TROMPELOEIL_ID(cardinality_match) =                                    \
    std::integral_constant<bool, num == ::trompeloeil::param_list<sig>::size>; \
  static_assert(TROMPELOEIL_ID(cardinality_match)::value,                      \
                "Function signature does not have " #num " parameters");       \
  using TROMPELOEIL_ID(matcher_list_t) = ::trompeloeil::call_matcher_list<sig>;\
  using TROMPELOEIL_ID(expectation_list_t) = ::trompeloeil::expectations<sig>; \
  mutable TROMPELOEIL_ID(expectation_list_t) TROMPELOEIL_ID(expectations);     \
  struct TROMPELOEIL_ID(tag_type_trompeloeil)                                  \
  {                                                                            \
    template <typename Mock>                                                   \
    struct maker_obj {                                                         \
      Mock& obj;                                                               \
      const char* file;                                                        \
      unsigned long line;                                                      \
      const char* call_string;                                                 \
                                                                               \
      template <typename ... U>                                                \
      auto name(                                                               \
        U&& ... u)                                                             \
      {                                                                        \
        using tag     = TROMPELOEIL_ID(tag_type_trompeloeil);                  \
        using params  = decltype(std::make_tuple(std::forward<U>(u)...));      \
        using matcher = ::trompeloeil::call_matcher<sig, params>;              \
        using info    = ::trompeloeil::matcher_info<sig>;                      \
        using modifier = ::trompeloeil::call_modifier<matcher, tag, info>;     \
                                                                               \
        auto  matcher_obj = std::make_unique<matcher>(file,                    \
                                                      line,                    \
                                                      call_string,             \
                                                      std::forward<U>(u)...);  \
        return modifier{std::move(matcher_obj)};                               \
      }                                                                        \
    };                                                                         \
    template <typename Mock>                                                   \
    static                                                                     \
    maker_obj<Mock>                                                            \
    maker(                                                                     \
      Mock& m_obj,                                                             \
      const char* file,                                                        \
      unsigned long line,                                                      \
      const char* name)                                                        \
    {                                                                          \
      return { m_obj, file, line, name };                                      \
    }                                                                          \
  };                                                                           \
                                                                               \
  TROMPELOEIL_ID(matcher_list_t)&                                              \
  trompeloeil_matcher_list(                                                    \
    TROMPELOEIL_ID(tag_type_trompeloeil))                                      \
  constness                                                                    \
  noexcept                                                                     \
  {                                                                            \
    return TROMPELOEIL_ID(expectations).active;                                \
  }                                                                            \
  ::trompeloeil::return_of_t<sig>                                              \
  name(                                                                        \
    TROMPELOEIL_PARAM_LIST(num, sig))                                          \
  constness                                                                    \
  spec                                                                         \
  {                                                                            \
    return ::trompeloeil::mock_func<sig>(TROMPELOEIL_ID(cardinality_match){},  \
                                         TROMPELOEIL_ID(expectations),         \
                                         #name,                                \
                                         #sig                                  \
                                         TROMPELOEIL_PARAMS(num));             \
  }                                                                            \
                                                                               \
  TROMPELOEIL_ID(tag_type_trompeloeil)                                         \
  trompeloeil_tag_ ## name(TROMPELOEIL_PARAM_LIST(num, sig)) constness




#define TROMPELOEIL_REQUIRE_CALL(obj, func)                                    \
  TROMPELOEIL_REQUIRE_CALL_(obj, func, #obj, #func)

#define TROMPELOEIL_REQUIRE_CALL_(obj, func, obj_s, func_s)                    \
  auto TROMPELOEIL_ID(call_obj) = TROMPELOEIL_REQUIRE_CALL_OBJ(obj, func,      \
                                                               obj_s, func_s)


#define TROMPELOEIL_NAMED_REQUIRE_CALL(obj, func)                              \
  TROMPELOEIL_NAMED_REQUIRE_CALL_(obj, func, #obj, #func)

#define TROMPELOEIL_NAMED_REQUIRE_CALL_(obj, func, obj_s, func_s)              \
  TROMPELOEIL_REQUIRE_CALL_OBJ(obj, func, obj_s, func_s)

#define TROMPELOEIL_REQUIRE_CALL_OBJ(obj, func, obj_s, func_s)                 \
  ::trompeloeil::call_validator(static_cast<std::decay_t<decltype((obj).func)>*>(nullptr), (obj)) + \
  decltype((obj).TROMPELOEIL_CONCAT(trompeloeil_tag_, func) )::maker(          \
    (obj), __FILE__, __LINE__, obj_s "." func_s \
  ).func

#define TROMPELOEIL_ALLOW_CALL(obj, func)                                      \
  TROMPELOEIL_ALLOW_CALL_(obj, func, #obj, #func)

#define TROMPELOEIL_ALLOW_CALL_(obj, func, obj_s, func_s)                      \
  TROMPELOEIL_REQUIRE_CALL_(obj, func, obj_s, func_s)                          \
    .TROMPELOEIL_TIMES(0, ~0ULL)


#define TROMPELOEIL_NAMED_ALLOW_CALL(obj, func)                                \
  TROMPELOEIL_NAMED_ALLOW_CALL_(obj, func, #obj, #func)

#define TROMPELOEIL_NAMED_ALLOW_CALL_(obj, func, obj_s, func_s)                \
  TROMPELOEIL_NAMED_REQUIRE_CALL_(obj, func, obj_s, func_s)                    \
    .TROMPELOEIL_TIMES(0, ~0ULL)

#define TROMPELOEIL_FORBID_CALL(obj, func)                                     \
  TROMPELOEIL_FORBID_CALL_(obj, func, #obj, #func)

#define TROMPELOEIL_FORBID_CALL_(obj, func, obj_s, func_s)                     \
  TROMPELOEIL_REQUIRE_CALL_(obj, func, obj_s, func_s)                          \
    .TROMPELOEIL_TIMES(0)                                                      \
    .THROW(false)

#define TROMPELOEIL_NAMED_FORBID_CALL(obj, func)                               \
  TROMPELOEIL_NAMED_FORBID_CALL_(obj, func, #obj, #func)

#define TROMPELOEIL_NAMED_FORBID_CALL_(obj, func, obj_s, func_s)               \
  TROMPELOEIL_NAMED_REQUIRE_CALL_(obj, func, obj_s, func_s)                    \
    .TROMPELOEIL_TIMES(0)                                                      \
    .THROW(false)



#define TROMPELOEIL_WITH(...)    TROMPELOEIL_WITH_(=,#__VA_ARGS__, __VA_ARGS__)
#define TROMPELOEIL_LR_WITH(...) TROMPELOEIL_WITH_(&,#__VA_ARGS__, __VA_ARGS__)

#define TROMPELOEIL_WITH_(capture, arg_s, ...)                                 \
  with(arg_s, [capture](auto const& trompeloeil_x) {                           \
    auto& _1 = ::trompeloeil::mkarg<1>(trompeloeil_x);                         \
    auto& _2 = ::trompeloeil::mkarg<2>(trompeloeil_x);                         \
    auto& _3 = ::trompeloeil::mkarg<3>(trompeloeil_x);                         \
    auto& _4 = ::trompeloeil::mkarg<4>(trompeloeil_x);                         \
    auto& _5 = ::trompeloeil::mkarg<5>(trompeloeil_x);                         \
    auto& _6 = ::trompeloeil::mkarg<6>(trompeloeil_x);                         \
    auto& _7 = ::trompeloeil::mkarg<7>(trompeloeil_x);                         \
    auto& _8 = ::trompeloeil::mkarg<8>(trompeloeil_x);                         \
    auto& _9 = ::trompeloeil::mkarg<9>(trompeloeil_x);                         \
    auto&_10 = ::trompeloeil::mkarg<10>(trompeloeil_x);                        \
    auto&_11 = ::trompeloeil::mkarg<11>(trompeloeil_x);                        \
    auto&_12 = ::trompeloeil::mkarg<12>(trompeloeil_x);                        \
    auto&_13 = ::trompeloeil::mkarg<13>(trompeloeil_x);                        \
    auto&_14 = ::trompeloeil::mkarg<14>(trompeloeil_x);                        \
    auto&_15 = ::trompeloeil::mkarg<15>(trompeloeil_x);                        \
    ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
    return __VA_ARGS__;                                                        \
  })

#define TROMPELOEIL_SIDE_EFFECT(...)    TROMPELOEIL_SIDE_EFFECT_(=, __VA_ARGS__)
#define TROMPELOEIL_LR_SIDE_EFFECT(...) TROMPELOEIL_SIDE_EFFECT_(&, __VA_ARGS__)

#define TROMPELOEIL_SIDE_EFFECT_(capture, ...)                                 \
  sideeffect([capture](auto& trompeloeil_x) {                                  \
    auto& _1 = ::trompeloeil::mkarg<1>(trompeloeil_x);                         \
    auto& _2 = ::trompeloeil::mkarg<2>(trompeloeil_x);                         \
    auto& _3 = ::trompeloeil::mkarg<3>(trompeloeil_x);                         \
    auto& _4 = ::trompeloeil::mkarg<4>(trompeloeil_x);                         \
    auto& _5 = ::trompeloeil::mkarg<5>(trompeloeil_x);                         \
    auto& _6 = ::trompeloeil::mkarg<6>(trompeloeil_x);                         \
    auto& _7 = ::trompeloeil::mkarg<7>(trompeloeil_x);                         \
    auto& _8 = ::trompeloeil::mkarg<8>(trompeloeil_x);                         \
    auto& _9 = ::trompeloeil::mkarg<9>(trompeloeil_x);                         \
    auto&_10 = ::trompeloeil::mkarg<10>(trompeloeil_x);                        \
    auto&_11 = ::trompeloeil::mkarg<11>(trompeloeil_x);                        \
    auto&_12 = ::trompeloeil::mkarg<12>(trompeloeil_x);                        \
    auto&_13 = ::trompeloeil::mkarg<13>(trompeloeil_x);                        \
    auto&_14 = ::trompeloeil::mkarg<14>(trompeloeil_x);                        \
    auto&_15 = ::trompeloeil::mkarg<15>(trompeloeil_x);                        \
    ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
    __VA_ARGS__;                                                               \
  })

#define TROMPELOEIL_RETURN(...)    TROMPELOEIL_RETURN_(=, __VA_ARGS__)
#define TROMPELOEIL_LR_RETURN(...) TROMPELOEIL_RETURN_(&, __VA_ARGS__)

#define TROMPELOEIL_RETURN_(capture, ...)                                      \
  handle_return([capture](auto& trompeloeil_x) -> decltype(auto) {             \
    auto& _1 = ::trompeloeil::mkarg<1>(trompeloeil_x);                         \
    auto& _2 = ::trompeloeil::mkarg<2>(trompeloeil_x);                         \
    auto& _3 = ::trompeloeil::mkarg<3>(trompeloeil_x);                         \
    auto& _4 = ::trompeloeil::mkarg<4>(trompeloeil_x);                         \
    auto& _5 = ::trompeloeil::mkarg<5>(trompeloeil_x);                         \
    auto& _6 = ::trompeloeil::mkarg<6>(trompeloeil_x);                         \
    auto& _7 = ::trompeloeil::mkarg<7>(trompeloeil_x);                         \
    auto& _8 = ::trompeloeil::mkarg<8>(trompeloeil_x);                         \
    auto& _9 = ::trompeloeil::mkarg<9>(trompeloeil_x);                         \
    auto&_10 = ::trompeloeil::mkarg<10>(trompeloeil_x);                        \
    auto&_11 = ::trompeloeil::mkarg<11>(trompeloeil_x);                        \
    auto&_12 = ::trompeloeil::mkarg<12>(trompeloeil_x);                        \
    auto&_13 = ::trompeloeil::mkarg<13>(trompeloeil_x);                        \
    auto&_14 = ::trompeloeil::mkarg<14>(trompeloeil_x);                        \
    auto&_15 = ::trompeloeil::mkarg<15>(trompeloeil_x);                        \
    ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
    return ::trompeloeil::decay_return_type(__VA_ARGS__);                                                        \
  })

#define TROMPELOEIL_THROW(...)    TROMPELOEIL_THROW_(=, __VA_ARGS__)
#define TROMPELOEIL_LR_THROW(...) TROMPELOEIL_THROW_(&, __VA_ARGS__)

#define TROMPELOEIL_THROW_(capture, ...)                                       \
  handle_throw([capture](auto& trompeloeil_x)  {                               \
    auto& _1 = ::trompeloeil::mkarg<1>(trompeloeil_x);                         \
    auto& _2 = ::trompeloeil::mkarg<2>(trompeloeil_x);                         \
    auto& _3 = ::trompeloeil::mkarg<3>(trompeloeil_x);                         \
    auto& _4 = ::trompeloeil::mkarg<4>(trompeloeil_x);                         \
    auto& _5 = ::trompeloeil::mkarg<5>(trompeloeil_x);                         \
    auto& _6 = ::trompeloeil::mkarg<6>(trompeloeil_x);                         \
    auto& _7 = ::trompeloeil::mkarg<7>(trompeloeil_x);                         \
    auto& _8 = ::trompeloeil::mkarg<8>(trompeloeil_x);                         \
    auto& _9 = ::trompeloeil::mkarg<9>(trompeloeil_x);                         \
    auto&_10 = ::trompeloeil::mkarg<10>(trompeloeil_x);                        \
    auto&_11 = ::trompeloeil::mkarg<11>(trompeloeil_x);                        \
    auto&_12 = ::trompeloeil::mkarg<12>(trompeloeil_x);                        \
    auto&_13 = ::trompeloeil::mkarg<13>(trompeloeil_x);                        \
    auto&_14 = ::trompeloeil::mkarg<14>(trompeloeil_x);                        \
    auto&_15 = ::trompeloeil::mkarg<15>(trompeloeil_x);                        \
    ::trompeloeil::ignore(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15); \
    throw __VA_ARGS__;                                                         \
 })


#define TROMPELOEIL_TIMES(...) times(::trompeloeil::multiplicity<__VA_ARGS__>{})

#define TROMPELOEIL_IN_SEQUENCE(...)                                           \
  in_sequence(TROMPELOEIL_INIT_WITH_STR(::trompeloeil::sequence_matcher::init_type, __VA_ARGS__))

#define TROMPELOEIL_ANY(type) ::trompeloeil::typed_wildcard<type>(#type)

#define TROMPELOEIL_AT_LEAST(num) num, ~0ULL
#define TROMPELOEIL_AT_MOST(num) 0, num

#define TROMPELOEIL_REQUIRE_DESTRUCTION(obj)                                   \
  TROMPELOEIL_REQUIRE_DESTRUCTION_(obj, #obj)

#define TROMPELOEIL_REQUIRE_DESTRUCTION_(obj, obj_s)                           \
  std::unique_ptr<trompeloeil::expectation>                                    \
    TROMPELOEIL_CONCAT(trompeloeil_death_monitor_, __LINE__)                   \
    = TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION_(,obj, obj_s)

#define TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION(obj)                             \
  TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION_("NAMED_", obj, #obj)

#define TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION_(prefix, obj, obj_s)                 \
  trompeloeil::lifetime_monitor_modifier<false>{                               \
    std::make_unique<trompeloeil::lifetime_monitor>(                           \
      obj,                                                                     \
      obj_s,                                                                   \
      prefix "REQUIRE_DESTRUCTION(" obj_s ")",                                 \
      "destructor for " obj_s,                                                 \
      ::trompeloeil::location{__FILE__,                                        \
                              static_cast<unsigned long>(__LINE__)})           \
  }

#ifndef TROMPELOEIL_LONG_MACROS
#define MAKE_MOCK0                TROMPELOEIL_MAKE_MOCK0
#define MAKE_MOCK1                TROMPELOEIL_MAKE_MOCK1
#define MAKE_MOCK2                TROMPELOEIL_MAKE_MOCK2
#define MAKE_MOCK3                TROMPELOEIL_MAKE_MOCK3
#define MAKE_MOCK4                TROMPELOEIL_MAKE_MOCK4
#define MAKE_MOCK5                TROMPELOEIL_MAKE_MOCK5
#define MAKE_MOCK6                TROMPELOEIL_MAKE_MOCK6
#define MAKE_MOCK7                TROMPELOEIL_MAKE_MOCK7
#define MAKE_MOCK8                TROMPELOEIL_MAKE_MOCK8
#define MAKE_MOCK9                TROMPELOEIL_MAKE_MOCK9
#define MAKE_MOCK10               TROMPELOEIL_MAKE_MOCK10
#define MAKE_MOCK11               TROMPELOEIL_MAKE_MOCK11
#define MAKE_MOCK12               TROMPELOEIL_MAKE_MOCK12
#define MAKE_MOCK13               TROMPELOEIL_MAKE_MOCK13
#define MAKE_MOCK14               TROMPELOEIL_MAKE_MOCK14
#define MAKE_MOCK15               TROMPELOEIL_MAKE_MOCK15

#define MAKE_CONST_MOCK0          TROMPELOEIL_MAKE_CONST_MOCK0
#define MAKE_CONST_MOCK1          TROMPELOEIL_MAKE_CONST_MOCK1
#define MAKE_CONST_MOCK2          TROMPELOEIL_MAKE_CONST_MOCK2
#define MAKE_CONST_MOCK3          TROMPELOEIL_MAKE_CONST_MOCK3
#define MAKE_CONST_MOCK4          TROMPELOEIL_MAKE_CONST_MOCK4
#define MAKE_CONST_MOCK5          TROMPELOEIL_MAKE_CONST_MOCK5
#define MAKE_CONST_MOCK6          TROMPELOEIL_MAKE_CONST_MOCK6
#define MAKE_CONST_MOCK7          TROMPELOEIL_MAKE_CONST_MOCK7
#define MAKE_CONST_MOCK8          TROMPELOEIL_MAKE_CONST_MOCK8
#define MAKE_CONST_MOCK9          TROMPELOEIL_MAKE_CONST_MOCK9
#define MAKE_CONST_MOCK10         TROMPELOEIL_MAKE_CONST_MOCK10
#define MAKE_CONST_MOCK11         TROMPELOEIL_MAKE_CONST_MOCK11
#define MAKE_CONST_MOCK12         TROMPELOEIL_MAKE_CONST_MOCK12
#define MAKE_CONST_MOCK13         TROMPELOEIL_MAKE_CONST_MOCK13
#define MAKE_CONST_MOCK14         TROMPELOEIL_MAKE_CONST_MOCK14
#define MAKE_CONST_MOCK15         TROMPELOEIL_MAKE_CONST_MOCK15

#define REQUIRE_CALL              TROMPELOEIL_REQUIRE_CALL
#define NAMED_REQUIRE_CALL        TROMPELOEIL_NAMED_REQUIRE_CALL
#define ALLOW_CALL                TROMPELOEIL_ALLOW_CALL
#define NAMED_ALLOW_CALL          TROMPELOEIL_NAMED_ALLOW_CALL
#define FORBID_CALL               TROMPELOEIL_FORBID_CALL
#define NAMED_FORBID_CALL         TROMPELOEIL_NAMED_FORBID_CALL
#define WITH                      TROMPELOEIL_WITH
#define LR_WITH                   TROMPELOEIL_LR_WITH
#define SIDE_EFFECT               TROMPELOEIL_SIDE_EFFECT
#define LR_SIDE_EFFECT            TROMPELOEIL_LR_SIDE_EFFECT
#define RETURN                    TROMPELOEIL_RETURN
#define LR_RETURN                 TROMPELOEIL_LR_RETURN
#define THROW                     TROMPELOEIL_THROW
#define LR_THROW                  TROMPELOEIL_LR_THROW
#define TIMES                     TROMPELOEIL_TIMES
#define IN_SEQUENCE               TROMPELOEIL_IN_SEQUENCE
#define ANY                       TROMPELOEIL_ANY
#define AT_LEAST                  TROMPELOEIL_AT_LEAST
#define AT_MOST                   TROMPELOEIL_AT_MOST
#define REQUIRE_DESTRUCTION       TROMPELOEIL_REQUIRE_DESTRUCTION
#define NAMED_REQUIRE_DESTRUCTION TROMPELOEIL_NAMED_REQUIRE_DESTRUCTION

#endif // TROMPELOEIL_LONG_MACROS

#endif // include guard
