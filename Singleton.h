#include <string>
#include <vector>
#include <list>
#include <queue>
#include <D:/uroki/New/SFML-2.4.2/include/SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>
using namespace sf;

class for_Singleton
{ 
  public:
  Image img;
  Texture imgt;
  Sprite imgs;
};


class Singleton
{
public:
  static Singleton &Instance();
  
  size_t insert_funk(Singleton &, std::string);
  Sprite get_from_cash(Singleton &, size_t);

private:
  Singleton();
  ~Singleton();
  Singleton(Singleton const &);
  Singleton &operator=(Singleton const &);
  std::unordered_map<size_t, Sprite> umap;
  size_t hash_fnk(Singleton &, std::string);
  double max_size;
  for_Singleton *vect;
  int i;
};