#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    //rectqngle bqr outil
    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLEUCLAIR);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(bouton1);
    bouton1.set_frame(0,0,90,90);//x,y,w,h
    bouton1.set_bg_color(NOIR);

    m_top_box.add_child(Tbouton1);
    Tbouton1.set_frame_pos(10,10);
    Tbouton1.set_message("TEST");
    Tbouton1.set_bg_color(BLANC);

    m_top_box.add_child(bouton2);
    bouton2.set_frame(0,90,90,90);//x,y,w,h
    bouton2.set_bg_color(ROUGE);

    m_top_box.add_child(Tbouton2);
    Tbouton2.set_frame_pos(10,150);
    Tbouton2.set_message("PROUT");
    Tbouton2.set_bg_color(BLANC);

    //m_top_box.add_child(bouton2);
    //bouton1.set_frame(0,400,100,100);//x,y,w,h
    //bouton1.set_bg_color(BLEU);


    //m_label_ajout_vertex.set_frame(0,0,100,100);//x,y,w,h
    //m_ajout_vertex.set_bg_color(NOIR);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 45.0, 200, 100, "lion.png");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);

    std::cout << "size map = " << m_vertices.size() << std::endl;

}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    // Faire les if de bouton
    //Exemple
    /*if(m_boutton.clique())
    {
        lirefichier("/fichier1.txt", deuxiemestring);//Fonction pour charger
        preupdate;

    }
    if(m_bouton.clique())
    {
        ajouter(); // Fonction ajouter qqch
        preupdate;
    }

*/

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();



           if(mouse_x > 20 && mouse_x <120 && mouse_y > 0 && mouse_y <120  )
       {
            supArete();
            this->supArete();

            for (auto &elt : m_vertices)
                elt.second.pre_update();

            for (auto &elt : m_edges)
                elt.second.pre_update();

            std::cout<<"WIN";
       }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    //m_edges[idx] = Edge(weight, ei);
    ///Correction
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;

    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);

}


void Graph::test_remove_edge(int eidx)
{
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);
        std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;
    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;
    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        /* m_interface->m_main_box.add_child(ei->m_top_edge); */
        /* m_edges[idx] = Edge(weight, ei); */
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }
    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );
    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );
    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;
}


// Lecture des fichiers textes
void Graph::lirefichier(std::string nomfichier,std::string dossier)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    std::ifstream fp;

    std::string chemin = dossier + nomfichier;
    std::cout << chemin << std::endl;

    //std::ifstream fp (chemin, std::ios::in)
    //Ouverture fichier texte des sommets
    fp.open(chemin);//string->const char
    // Lecture fichier texte des sommets
    if(fp)
    {
        // On declare les variables
        std::string lettre ="";
        int chiffre=0;
        double chiffre2=0;
        int chiffre3=0;
        int chiffre4=0;
        fp >> m_ordre;
        std::cout << "L'ordre du graphe est : " << m_ordre << std::endl;

        for (int i=0; i<m_ordre;i++)
        {
        std::cout << "i = " << i << std::endl;
        fp >> chiffre;
        fp >> lettre;
        fp >> chiffre2;
        fp >> chiffre3;
        fp >> chiffre4;
        std::cout << chiffre << " " << lettre << " " << chiffre2 << " " << chiffre3 << " " << chiffre4 << " " << std::endl;
        add_interfaced_vertex(chiffre, chiffre2, chiffre3, chiffre4, lettre);


        }

        int indice=0;
        int sommet1=0;
        int sommet2=0;
        double poids=0;
        fp >> m_degres;

        //fp >> m_ordre;
        //std::cout << "L'ordre du graphe est : " << m_ordre << std::endl;

        for (int j=0; j<m_degres;j++)
        {
        std::cout << "j = " << j << std::endl;
        fp >> indice;
        fp >> sommet1;
        fp >> sommet2;
        fp >> poids;
        //fp >> chiffre4;
        std::cout << indice << " " << sommet1 << " " << sommet2 << " " << poids << " " << std::endl;
        add_interfaced_edge(indice, sommet1, sommet2, poids);

        }

}
    //Fermeture fichier texte sommet une fois que les donnees sont recuperees
    fp.close();
}


void Graph::addsommet() //Fonction qui ajoute un sommet
{
    // Declarer les variables
    std::string nom_sommet;
    double valeur_sommet;
    // Saisir les variables
    std::cout << "Entrez le nom du sommet " << std::endl;
    std::cin >> nom_sommet;
    std::cout << "Entrez la valeur du sommet" << std::endl;
    std::cin >> valeur_sommet;

    // Fonction qui permet l'ajout d'un sommet
    add_interfaced_vertex(m_vertices.size(), valeur_sommet, 125, 10, nom_sommet);

}


void Graph::addArete() // Fonction qui ajoute une arete entre deux sommets
{
    // Declarer les variables
    int indice_s1, indice_s2;
    double poids;
    // Saisir les variables
    std::cout << "Entrez l'indice du sommet de depart" << std::endl;
    std::cin >> indice_s1;
    std::cout << "Entrez l'indice du sommet de depart" << std::endl;
    std::cin >> indice_s2;
    std::cout << "Entrez le poids de l'arete" << std::endl;
    std::cin >> poids;

    // Fonction qui permet l'ajout d'une arete entre deux sommets
    add_interfaced_edge(m_edges.size(), indice_s1, indice_s2, poids);

}

/*
void Graph::supArete()
{
    int indice_s1;
    int indice_s2;
    int i;
    int indice_arete;

    std::cout << " Entrer l'indice du sommet de depart:";
    std::cin >> indice_s1;
    std::cout << " Entrer l'indice du sommet d'arrivee:";
    std::cin >> indice_s2;

            for  (auto elem : m_edges)
            {
                if ((m_vertices.count(indice_s1))+(m_vertices.count(indice_s2)) == 2)
        {


                if (elem.second.m_from == indice_s1 && elem.second.m_to == indice_s2)
                {
                    indice_arete = elem.first;
                    test_remove_edge(indice_arete);
                }

            }
}}
*/


void Graph::supArete()
{
    int indice_s1;
    int indice_s2;
    int i;
    int indice_arete;

    std::cout << " Entrer l'indice du sommet de depart:";
    std::cin >> indice_s1;
    std::cout << " Entrer l'indice du sommet d'arrivee:";
    std::cin >> indice_s2;

for (i=0; i<m_edges.size(); i++)
{
        if ((m_vertices.count(indice_s1))+(m_vertices.count(indice_s2)) == 2)
        {
            for  (auto elem : m_edges)
            {
                if (elem.second.m_from == indice_s1 && elem.second.m_to == indice_s2)
                {
                    indice_arete = elem.first;
                    test_remove_edge(indice_arete);
                }
            }

        }
}
}


/*
void Graph::barreoutils()
{
    //Decalaration variables
    int color;
    int mouse_prec;
    int mouse_suiv;


    // Declarer les btimap
    BITMAP *page;
    BITMAP *add_sommet;
    BITMAP *add_arete;
    BITMAP *retour_menu;
    BITMAP *quitter;
    BITMAP *collision;
    BITMAP *bmp;

    //Initialisation allegro
    page= create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // Chargement des bitmaps c'est a dire des images

     collision=load_bitmap("sommet.jpg", NULL);
    if (!collision)
    {
        allegro_message("IMAGE INTROUVABLE");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    add_sommet=load_bitmap("sommet.jpg", NULL);
    if (!add_sommet)
    {
        allegro_message("IMAGE INTROUVABLE");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    add_arete=load_bitmap("arete.jpg", NULL);
    if (!add_arete)
    {
        allegro_message("IMAGE INTROUVABLE");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    retour_menu=load_bitmap("menu.jpg", NULL);
    if (!retour_menu)
    {
        allegro_message("IMAGE INTROUVABLE");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    quitter=load_bitmap("quitter.jpg", NULL);
    if (!quitter)
    {
        allegro_message("IMAGE INTROUVABLE");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    bmp=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    //Afficher les boutons de la barre d'outils
    draw_sprite(bmp, add_sommet, 10, 10);
    draw_sprite(bmp, add_arete, 50, 10);
    draw_sprite(bmp, retour_menu, 90, 10);
    draw_sprite(bmp, quitter, 130, 10);


    //Recuperer la couleur de la carte de collision
    color= getpixel(collision, mouse_x, mouse_y);

    mouse_prec= mouse_suiv;
    mouse_suiv= mouse_b;

    // si la souris est sur la position de la case alors....

    if( color== makecol(0, 255, 0))
       {
           if (!(mouse_prec&1)&&(mouse_suiv&1))
        {

        }
       }

    if( color== makecol(255, 255, 0))
       {
           if (!(mouse_prec&1)&&(mouse_suiv&1))
        {
            int s1, s2, weight;
            std::cout << "Entrez l'indice du sommet de depart" << std::endl;
            std::cin >> s1;
            std::cout << "Entrez l'indice du sommet d'arrivee" << std::endl;
            std::cin >> s2;
            std::cout << "Entrez le poids de l'arete" << std::endl;
            std::cin >> weight;
            add_interfaced_edge(m_vertices.end(idx+1), s1, s2, weight);

        }
       }

    if (color== makecol(255,0,0))
       {
           if (!(mouse_prec&1)&&(mouse_suiv&1))
           {

           }
       }

    if(color== makecol(0,0,255))
       {
           if (!(mouse_prec&1)&&(mouse_suiv&1))
           {
               allegro_exit();
               exit(EXIT_SUCCESS);
           }
       }

    blit(bmp,screen,0,0,0,0,SCREEN_W,SCREEN_H);

}
*/
