#include <functional>

namespace result {
  enum Type { E_Ok, E_Err };

  template <typename V, typename E>
  class Result {
  protected:
    Result(V val) :type(E_Ok), v(std::move(val)) {}
    Result(E err) :type(E_Err), e(std::move(err)) {}
  public:
    Result<V,E> if_err(std::function<void(E)>) const;
    Result<V,E> if_ok(std::function<void(V)>) const;
    bool        as_bool() const;
    V           val() const;
    E           err() const;

  public:
    static Result<V,E> Err(E);
    static Result<V,E> Ok(V);

  private:
    Type type;
    V v;
    E e;
  };

  template <typename V, typename E>
  Result<V,E> Result<V,E>::Err(E err) {
    return Result<V,E>(err);
  }

  template <typename V, typename E>
  Result<V,E> Result<V,E>::Ok(V ok) {
    return Result<V,E>(ok);
  }

  template <typename V, typename E>
  Result<V,E> Result<V,E>::if_err(std::function<void(E)> func) const {
    if (type == E_Err) {
      func(e);
    }
    return *this;
  }

  template <typename V, typename E>
  Result<V,E> Result<V,E>::if_ok(std::function<void(V)> func) const {
    if (type == E_Ok) {
      func(v);
    }
    return *this;
  }

  template <typename V, typename E>
  bool Result<V,E>::as_bool() const {
    return type == E_Ok;
  }

  template <typename V, typename E>
  V Result<V,E>::val() const {
    return v;
  }

  template <typename V, typename E>
  E Result<V,E>::err() const {
    return e;
  }
}
