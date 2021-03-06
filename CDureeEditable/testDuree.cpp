/**
 *
 * @file    TestDuree.cpp
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    17/03/2010
 *
 * @version V1.0
 *
 * @brief   Test de la classe CDuree complete
 *
 **/
#include <ostream>
#include <cassert>
#include <sstream>
#include <exception>
#include <utility>
#include <iomanip>


#include "CException.h"    // de l'exercice précédent
#include "CstCodErr.h"
#include "Duree.h"
#include "IEditable.hpp"

using namespace std;
using namespace rel_ops;
using namespace nsUtil;    // CException

namespace
{
    class DureeEditable : public Duree, public IEditable {

    protected:
        virtual void display (ostream & os) const {
            os << '['
                 << setw (6) << myDays    << ':'
                 << setfill ('0')
                 << setw (2)  << myHours   << ":"
                 << setw (2)  << myMinutes << ":"
                 << setw (2)  << mySeconds
                 << setfill (' ')
                 << ']' << std::flush;
        }

    public:
        explicit DureeEditable(unsigned long long d = 0) : Duree(d), IEditable() {}
        DureeEditable(const Duree & duree) : Duree(duree){}
        virtual ~DureeEditable(){}
        DureeEditable & operator ++ (void) noexcept {
            *this = Duree::operator++();
            return *this;
        } // préincrémentation de la classe Duree
        DureeEditable operator ++ (int i)  noexcept {
           return Duree::operator++(i);
        } // postincrémentation de la classe Duree
        DureeEditable & operator -- (void) noexcept {
            *this = Duree::operator--();
            return *this;
        } // préincrémentation de la classe Duree
        DureeEditable   operator -- (int i)  noexcept {
           return Duree::operator--(i);

        } // postincrémentation de la classe Duree

        DureeEditable & operator += (const Duree & d) noexcept {
            *this =Duree::operator+=(d);
            return *this;
        }
        DureeEditable & operator -= (const Duree & d) noexcept {
            *this = Duree::operator-=(d);
            return *this;
        }
        DureeEditable & operator -= (const unsigned long long & Duree) noexcept {
            *this = Duree::operator-=(Duree);
            return *this;
        }
        DureeEditable & operator += (const unsigned long long & Duree) noexcept {
            *this = Duree::operator+=(Duree);
            return *this;
        }


    };

    void testDuree_01 (void)
    {
        DureeEditable d1 (3661);
        DureeEditable d2 (2661);
        DureeEditable d3 (3661);

        assert (! (d1 < d2));
        assert (  (d2 < d1));

        assert (   d1 > d2);
        assert (! (d2 > d1));

        assert (! (d1 <= d2));
        assert (   d2 <= d1);

        assert (   d1 >= d2);
        assert (! (d2 >= d1));

        assert (! (d1 == d2));
        assert (! (d2 == d1));
        assert (   d1 == d3);

        assert (   d1 != d2);
        assert (   d2 != d1);

    } // testDuree_01()

    void testDuree_02 (void)
    {
        DureeEditable d1 (3661);
        {
            ostringstream oss;
            oss << d1;
            assert (oss.str() == "[     0:01:01:01]");
        }
        {
            ostringstream oss;
            oss << d1--;
            assert (oss.str() == "[     0:01:01:01]");
        }
        {
            ostringstream oss;
            oss << d1--;
            assert (oss.str() == "[     0:01:01:00]");
        }
        {
            ostringstream oss;
            oss << --d1;
            assert (oss.str() == "[     0:01:00:58]");
        }
        {
            ostringstream oss;
            oss << d1;
            assert (oss.str() == "[     0:01:00:58]");
        }
        {
            ostringstream oss;
            oss << d1++;
            assert (oss.str() == "[     0:01:00:58]");
        }
        {
            ostringstream oss;
            oss << d1++;
            assert (oss.str() == "[     0:01:00:59]");
        }
        {
            ostringstream oss;
            oss << ++d1;
            assert (oss.str() == "[     0:01:01:01]");
        }
        {
            ostringstream oss;
            oss << ++d1;
            assert (oss.str() == "[     0:01:01:02]");
        }
        {
            ostringstream oss;
            oss << ++d1;
            assert (oss.str() == "[     0:01:01:03]");
        }
        {
            ostringstream oss;
            oss << (d1 -= 3);
            assert (oss.str() == "[     0:01:01:00]");
        }
        {
            ostringstream oss;
            oss << (d1 += 3);
            assert (oss.str() == "[     0:01:01:03]");
        }
        {
            ostringstream oss;
            oss << (d1 += Duree (3));
            assert (oss.str() == "[     0:01:01:06]");
        }
        {
            d1.setDuree (0);
            ostringstream oss;
            oss << d1;
            assert (oss.str() == "[     0:00:00:00]");
        }

    } // testDuree_02)

    void testDuree_03 (void)
    {
        DureeEditable d1;
        bool isCaught = false;

        try { d1--; }
        catch (const CException & e) { isCaught = true; }
        assert (isCaught);

        isCaught = false;
        try { --d1; }
        catch (const CException & e) { isCaught = true; }
        assert (isCaught);

        isCaught = false;
        try { d1 -= 1; }
        catch (const CException & e) { isCaught = true; }
        assert (isCaught);

        isCaught = false;
        try { d1 -= Duree (3); }
        catch (const CException & e) { isCaught = true; }
        assert (isCaught);

    } // testDuree_03()

} // namespace anonyme

int main (int argc, char * argv [])
{
    if (argc != 1)
    {
        cerr << "Nombre d'arguments invalide\n"
                "Usage : TestCDuree\n";
        return 0;
    }
    try
    {
        testDuree_01 ();
        testDuree_02 ();
        testDuree_03 ();
        cout << "Fin normale\n";

        return KNoExc;
    }
    catch (const CException & e)
    {
        cerr << e << '\n';
        return e.getCodErr();
    }
    catch (const exception & e)
    {
        cerr << "Exception standard : " << e.what() << '\n';
        return KExcStd;
    }
    catch (...)
    {
        cerr << "Exception inconnue\n";
        return KExcInconnue;
    }

} // main()
