#include "grman/grman.h"
#include <iostream>

#include "graph.h"
/// MASBERNAT Salome- ROBILLARD Julia
/// Sources: Cours de Mr Segado, Cours de Mme Palasi, Reference C++, Open class room
/// Travail en collaboration avec l'equipe 11 du td7 ( Levanah MASBERNAT, Alice BORIE, Mathieu BAUMAS).

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    Graph g;

    /// Le nom du répertoire où se trouvent les images à charger
    // Appel du menu du jeu
    std::string deuxiemestring = g.menu_jeu();
    std::cout << "deuxiemestring =" << deuxiemestring << std::endl;
    if(deuxiemestring!="quitter")
    {
        grman::set_pictures_path(deuxiemestring);

        /// Lecture du fichier texte
        g.lirefichier("/fichier.txt", deuxiemestring);

        /// Vous gardez la main sur la "boucle de jeu"
        /// ( contrairement à des frameworks plus avancés )
        while ( !key[KEY_ESC] )
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update(deuxiemestring);

            /*if(mouse_x > 20 && mouse_x <120 && mouse_y > 0 && mouse_y <120  )
            {
                g.supArete();
                std::cout<<"WIN";
            }*/
            // Trouver les coordonnees de la souris
            //std::cout<<mouse_x;
            //std::cout<<" ";

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }
    }


    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


