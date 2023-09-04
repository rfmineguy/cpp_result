#include <functional>

namespace result {
  enum Type { E_Ok, E_Err };

  template <typename V, typename E>
  class Result {
  public:
    Result(V val) :type(E_Ok), val(val) {}
    Result(E err) :type(E_Err), err(err) {}
    void if_err(std::function<void(E)>);
    void if_ok(std::function<void(V)>);

  private:
    Type type;
    V val;
    E err;
  };

  template <typename V, typename E>
  Result<V,E> Err(E err, V val = {}) {
    return Result<V,E>(err);
  }

  template <typename V, typename E>
  Result<V,E> Ok(V ok, E err = {}) {
    return Result<V,E>(ok);
  }

  template <typename V, typename E>
  void Result<V,E>::if_err(std::function<void(E)> func) {
    if (type == E_Err) {
      func(err);
    }
  }

  template <typename V, typename E>
  void Result<V,E>::if_ok(std::function<void(V)> func) {
    if (type == E_Ok) {
      func(val);
    }
  }
}
