/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 */

#include <fatal/type/pair.h>

#ifndef FATAL_INCLUDE_fatal_type_impl_group_by_h
#define FATAL_INCLUDE_fatal_type_impl_group_by_h

namespace fatal {
namespace impl_gby {

template <template <typename> class, typename...> struct gby;
template <template <typename> class, typename...> struct gbys;

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename GroupKey,
  typename... Group,
  typename... Result,
  typename NextKey,
  typename T,
  typename... Args
>
struct gbys<
  Key,
  GroupKey, Variadics<Group...>,
  Variadics<Result...>,
  NextKey, T,
  Args...
>:
  gby<
    Key,
    Variadics<T>,
    Variadics<Result..., pair<GroupKey, Variadics<Group...>>>,
    Args...
  >
{};

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename GroupKey,
  typename... Group,
  typename... Result,
  typename T,
  typename... Args
>
struct gbys<
  Key,
  GroupKey, Variadics<Group...>,
  Variadics<Result...>,
  GroupKey, T,
  Args...
>:
  gby<Key, Variadics<Group..., T>, Variadics<Result...>, Args...>
{};

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename... Result
>
struct gby<Key, Variadics<>, Variadics<Result...>> {
  using type = Variadics<Result...>;
};

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename G,
  typename... Group,
  typename... Result
>
struct gby<Key, Variadics<G, Group...>, Variadics<Result...>> {
  using type = Variadics<Result..., pair<Key<G>, Variadics<G, Group...>>>;
};

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename... Result,
  typename T,
  typename... Args
>
struct gby<Key, Variadics<>, Variadics<Result...>, T, Args...>:
  gby<Key, Variadics<T>, Variadics<Result...>, Args...>
{};

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename G,
  typename... Group,
  typename... Result,
  typename T,
  typename... Args
>
struct gby<Key, Variadics<G, Group...>, Variadics<Result...>, T, Args...>:
  gbys<
    Key,
    Key<G>, Variadics<G, Group...>,
    Variadics<Result...>,
    Key<T>, T,
    Args...
  >
{};

template <template <typename> class, typename...> struct group;

template <
  template <typename> class Key,
  template <typename...> class Variadics,
  typename... Args
>
struct group<Key, Variadics<Args...>>:
  gby<Key, Variadics<>, Variadics<>, Args...>
{};

template <template <typename> class, template <typename> class, typename...>
struct fgby;

template <template <typename> class, template <typename> class, typename...>
struct fgbys;

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename GroupKey,
  typename... Group,
  typename... Result,
  typename NextKey,
  typename T,
  typename... Args
>
struct fgbys<
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  GroupKey, Variadics<Group...>,
  Variadics<Result...>,
  NextKey, T,
  Args...
>:
  fgby<
    Key,
    RejectPredicate,
    RejectedGrouping<Rejected...>,
    Variadics<T>,
    Variadics<Result..., pair<GroupKey, Variadics<Group...>>>,
    Args...
  >
{};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename GroupKey,
  typename... Group,
  typename... Result,
  typename T,
  typename... Args
>
struct fgbys<
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  GroupKey, Variadics<Group...>,
  Variadics<Result...>,
  GroupKey, T,
  Args...
>:
  fgby<
    Key,
    RejectPredicate,
    RejectedGrouping<Rejected...>,
    Variadics<Group..., T>,
    Variadics<Result...>,
    Args...
  >
{};

template <
  bool,
  template <typename> class,
  template <typename> class,
  typename...
>
struct fgbyr;

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename G,
  typename... Group,
  typename... Result,
  typename T,
  typename... Args
>
struct fgbyr<
  false,
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  Variadics<G, Group...>,
  Variadics<Result...>,
  T, Args...
> {
  using type = fgbys<
    Key,
    RejectPredicate,
    RejectedGrouping<Rejected...>,
    Key<G>, Variadics<G, Group...>,
    Variadics<Result...>,
    Key<T>, T,
    Args...
  >;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename... Result,
  typename T,
  typename... Args
>
struct fgbyr<
  false,
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  Variadics<>,
  Variadics<Result...>,
  T, Args...
> {
  using type = fgby<
    Key,
    RejectPredicate,
    RejectedGrouping<Rejected...>,
    Variadics<T>,
    Variadics<Result...>,
    Args...
  >;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename... Group,
  typename... Result,
  typename T,
  typename... Args
>
struct fgbyr<
  true,
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  Variadics<Group...>,
  Variadics<Result...>,
  T, Args...
> {
  using type = fgby<
    Key,
    RejectPredicate,
    RejectedGrouping<Rejected..., T>,
    Variadics<Group...>,
    Variadics<Result...>,
    Args...
  >;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  template <typename...> class Variadics,
  typename... Result
>
struct fgby<
  Key,
  RejectPredicate,
  RejectedGrouping<>,
  Variadics<>,
  Variadics<Result...>
> {
  using type = Variadics<Result...>;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename... Result
>
struct fgby<
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  Variadics<>,
  Variadics<Result...>
> {
  using type = Variadics<RejectedGrouping<Rejected...>, Result...>;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  template <typename...> class Variadics,
  typename G,
  typename... Group,
  typename... Result
>
struct fgby<
  Key,
  RejectPredicate,
  RejectedGrouping<>,
  Variadics<G, Group...>,
  Variadics<Result...>
> {
  using type = Variadics<Result..., pair<Key<G>, Variadics<G, Group...>>>;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename G,
  typename... Group,
  typename... Result
>
struct fgby<
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  Variadics<G, Group...>,
  Variadics<Result...>
> {
  using type = Variadics<
    RejectedGrouping<Rejected...>,
    Result...,
    pair<Key<G>, Variadics<G, Group...>>
  >;
};

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  typename... Rejected,
  template <typename...> class Variadics,
  typename... Group,
  typename... Result,
  typename T,
  typename... Args
>
struct fgby<
  Key,
  RejectPredicate,
  RejectedGrouping<Rejected...>,
  Variadics<Group...>,
  Variadics<Result...>,
  T, Args...
>:
  fgbyr<
    RejectPredicate<T>::value,
    Key,
    RejectPredicate,
    RejectedGrouping<Rejected...>,
    Variadics<Group...>,
    Variadics<Result...>,
    T, Args...
  >::type
{};

template <
  template <typename> class,
  template <typename> class,
  template <typename...> class,
  typename...
>
struct filtered;

template <
  template <typename> class Key,
  template <typename> class RejectPredicate,
  template <typename...> class RejectedGrouping,
  template <typename...> class Variadics,
  typename... Args
>
struct filtered<
  Key,
  RejectPredicate,
  RejectedGrouping,
  Variadics<Args...>
>:
  fgby<
    Key,
    RejectPredicate,
    RejectedGrouping<>,
    Variadics<>,
    Variadics<>,
    Args...
  >
{};

} // namespace impl_gby {
} // namespace fatal {

#endif // FATAL_INCLUDE_fatal_type_impl_group_by_h
