/*
 * Una funcion f: R->R es escalonada cuando consiste en una sucesion de funciones constantes
 * definidas en subintervalos disjuntos y contiguos, es decir, f puede definirse mediante
 * condiciones de la forma f(x) = y_i si x_i <= x < x_i+1, donde los valores y_i son distintos
 * para subintervalos adyacentes. Cada uno de los puntos (x_i, y_i) en los que la funcion
 * cambia de valor se llama salto o escalon.
 */

#include <iostream>
#include <lista_enla_cab.h>

class FuncEscalonada {
  private:
    struct escalon {
      float inicio;
      float fin;
      escalon( float ini = .0f, float fini = .0f ) :
        inicio( ini ), fin( fini ) {}
    };
    Lista<escalon> escalones;
  public:
    typedef escalon escalon;

    FuncEscalonada( float x, float y ) {
      escalon esc { x, y };
      escalones.insertar( esc, escalones.fin() );
    }

    /* Metodos */

    friend std::ostream& operator <<( std::ostream& os, const FuncEscalonada& FE );
    ~FuncEscalonada() {}
};

std::ostream& operator <<( std::ostream& os, const FuncEscalonada& FE ) {

  auto pos = FE.escalones.primera();

  for( ; pos != FE.escalones.fin(); pos = FE.escalones.siguiente( pos ) ) {
    os << FE.escalones.elemento( pos ).inicio << " | " << FE.escalones.elemento( pos ).fin << '\n';
  }

  return os;
}

int main( void ) 
{
  FuncEscalonada F{1,1};

  std::cout << F;

  return 0;
}
