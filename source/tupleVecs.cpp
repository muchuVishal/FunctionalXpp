#include <iostream>
#include <string>

#include <tuple>
#include <utility>
#include <vector>
#include <string>
#include <experimental/tuple>
#include <sstream>

 double getDouble( const std::string& s )
 {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
 } 
    
int getInt32( const std::string& s )
 {
   std::istringstream i(s);
   int x;
   if (!(i >> x))
     return 0;
   return x;
 }     
 
 uint getUInt32( const std::string& s )
 {
   std::istringstream i(s);
   uint x;
   if (!(i >> x))
     return 0;
   return x;
 }    
    
template <typename T> 
auto variadic_tuple(const T t) {
    return std::tie(t);
}
    
template <typename First, typename... Rest> 
auto variadic_tuple(const First& first, const Rest&... rest) {
    return std::tuple_cat(std::tie(first), variadic_tuple(rest...));
}
    
template <typename Tup, typename T>
auto extended_tuple(const Tup tup, const T t) {
	return std::tuple_cat(tup, std::make_tuple(t));
}

template < typename T>
void print(const T& t) {
	std::cout << t << std::endl;
}
template < typename First, typename... Rest >
void print(const First& f, const Rest&... r) {
	std::cout << f << ", ";
	print(r...);
}

template<std::size_t> struct int_{};

template <class Tuple, size_t Pos>
void print_tuple( const Tuple& t, int_<Pos> ) {
  std::cout << std::get< std::tuple_size<Tuple>::value-Pos >(t) << ',';
  print_tuple( t, int_<Pos-1>());
}

template <class Tuple>
void print_tuple(const Tuple& t, int_<1> ) {
  std::cout << std::get<std::tuple_size<Tuple>::value-1>(t);
}


template <typename... Args  >
void print_tuple(const std::tuple<Args...>& tup) {
	print_tuple(tup, int_<sizeof...(Args)>());
}


void foo(int a, const std::string& b, float c)
   {
       std::cout << a << " , " << b << " , " << c << '\n';
   }
    
int main() {
    std::tuple<double, int> test;
    auto test2 = std::tuple<double, int> ();
    
    std::vector<std::string> cols = {"0.5", "1"};
    double d = getDouble("1.1");
	std::cout << d << std::endl;
	
	
	
	std::vector<std::string> datastr1 {"1.1", "2", "hello"};
		std::vector<std::string> datastr2{"1.1", "2", "hello"};
std::vector<std::vector<std::string>> datastrs {datastr1, datastr2};

std::vector<std::tuple<int, double, int, std::string>> tupvec;
for (int i = 0; i != 2; ++ i) {
	auto tup0 = std::make_tuple(i);
	auto tup1 = extended_tuple(tup0, getDouble(datastrs[i][0]));
	auto tup2 = extended_tuple(tup1, getInt32(datastrs[i][1]));
	auto tup3 = extended_tuple(tup2, datastrs[i][2]);
	tupvec.push_back(tup3);	
}
   	auto args = variadic_tuple(2, "Hello", 3.5);
    std::experimental::apply(foo, args);
    
    for (int i = 0; i != 2; ++i) {
    	print_tuple(tupvec[i]);
    	std::cout << std::endl;
    }
    print("1.1", 0, "hello");
       return 0;
   }

