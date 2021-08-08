/*
 * La direccion de un hospital quiere informatizar su consultorio medico con un programa
 * que realice las siguientes operaciones:
 *  - Generar un consultorio vacio
 *  - Dar de alta/baja un medico
 *  - Poner a un paciente en la lista de espera de un medico
 *  - Consultar al paciente a quien le toca el turno para ser atendido
 *  - Atender al paciente que le toque por parte de un medico
 *  - Comprobar si un medico determinado tiene o no pacientes en espera
 */
#include <cstring>
#include <iostream>
#include <lista_enla_cab.h>
#include <cola.h>


class Consultorio {
private:
    struct __medico {
        char* nombre;
        char* apellido;
        char* identificador;
        cola<char*> pacientes;
        __medico ( const char* n = "\0", const char* a = "\0", const char* id = "\0" ) :
            nombre       ( new char[ std::strlen(n)  + 1 ] ),
            apellido     ( new char[ std::strlen(a)  + 1 ] ),
            identificador( new char[ std::strlen(id) + 1 ] )
        {
            std::strcpy( nombre, n );
            std::strcpy( apellido, a );
            std::strcpy( identificador, id );
        }
    };
    Lista<__medico> medicos;

    typename Lista<__medico>::posicion
    buscar_medico( const __medico& med ) const {
        auto pos = medicos.primera();

        for( ; pos != medicos.fin(); pos = medicos.siguiente( pos ) ) {
            if ( std::strcmp( med.identificador,
                medicos.elemento( pos ).identificador ) == 0 ) {
                
                return pos;
            }
        }

        return pos;
    }

public:
    typedef __medico medico;
    Consultorio() {}
    
    /* Metodos*/
    void alta_medico( const medico& med ) {
        medicos.insertar( med, medicos.fin() );
    }

    void baja_medico( const medico& med ) {
        auto pos_medico = buscar_medico( med );
        medicos.eliminar( pos_medico );
    }

    bool tiene_pacientes( const medico& med ) {
        auto pos_medico = buscar_medico( med );

        if ( pos_medico == medicos.fin()) {
            return false;
        }

        if ( medicos.elemento( pos_medico ).pacientes.vacia() ) {
            return false;
        }
        return true;
    }

    void nuevo_paciente( char* const pac, const medico& med ) {
        auto pos_medico = buscar_medico( med );
        if ( pos_medico == medicos.fin() ) {
        } else {
            medicos.elemento( pos_medico ).pacientes.push( pac );
        }
    }

    const char* consultar_paciente( const medico& med ) const {
        auto pos_medico = buscar_medico( med );
        if ( pos_medico == medicos.fin() ) {
            return nullptr;
        } else {
            return medicos.elemento( pos_medico ).pacientes.return_output();
        }
    }
    void atender_paciente( const medico& med ) {
        auto pos_medico = buscar_medico( med );
        if ( pos_medico == medicos.fin() ) {
        } else {
            medicos.elemento( pos_medico ).pacientes.pop();
        }
    }

    ~Consultorio() {}
};

int main( ) 
{
    Consultorio C;
    Consultorio::medico med {"Fernando", "Pojo", "12345"};
    C.alta_medico( med );
    C.nuevo_paciente( (char* const)"Fernanflo", med );
    std::cout << C.consultar_paciente( med ) << std::endl;
    return 0;
}