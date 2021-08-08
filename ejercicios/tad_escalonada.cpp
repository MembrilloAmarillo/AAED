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
      float y;
      escalon( float ini = .0f, float fini = .0f, float _y = .0f ) :
        inicio( ini ), fin( fini ), y(_y) {}
    };
    Lista<escalon> escalones;

    bool se_interponen( escalon a, escalon b )
    {
      if ( a.inicio >= b.inicio && a.inicio <= b.fin ) {
        return true;
      } else if ( a.inicio <= b.inicio && a.fin >= b.fin ) {
        return true;
      } else if ( a.fin >= b.inicio ) {
        return true;
      } else {
        return false;
      }
    }
  public:
    typedef escalon _escalon;

    FuncEscalonada( float ini, float fin, float y ) {
      escalon esc { y, ini, fin };
      escalones.insertar( esc, escalones.fin() );
    }

    /* Metodos */

    void insertar( escalon esc ) 
    {
      auto pos = escalones.primera();
      for( ; pos != escalones.fin(); pos = escalones.siguiente( pos ) ) {
        if( se_interponen( escalones.elemento( pos ), esc ) ) {
          escalones.eliminar( pos );
        }
      }
      escalones.insertar( esc, escalones.fin() );
    }

    friend std::ostream& operator <<( std::ostream& os, const FuncEscalonada& FE );
    ~FuncEscalonada() {}
};

std::ostream& operator <<( std::ostream& os, const FuncEscalonada& FE ) {

  auto pos = FE.escalones.primera();

  for( ; pos != FE.escalones.fin(); pos = FE.escalones.siguiente( pos ) ) {
    os << FE.escalones.elemento( pos ).inicio << " | "
        << FE.escalones.elemento( pos ).fin   << " | "
        << FE.escalones.elemento( pos ).y     << '\n';
  }
  return os;
}

int main( void ) 
{
  FuncEscalonada F{1, 1, 1};

  FuncEscalonada::_escalon esc {3, 1, 4};

  F.insertar(esc);
  F.insertar({0, 2, 3});
  F.insertar({-1, 5, 6});
  F.insertar({3, 4, 6});

  std::cout << F;

  return 0;
}
