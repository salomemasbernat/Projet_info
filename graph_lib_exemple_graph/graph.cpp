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
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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
    m_tool_box.set_bg_color(BLANC);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    /// Bouton 1 qui va être utilise pour le retour au menu
    m_top_box.add_child(bouton1);
    bouton1.set_frame(0,0,90,80);//x,y,w,h
    bouton1.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton1);
    Tbouton1.set_frame_pos(20,40);
    Tbouton1.set_message("RETURN");
    Tbouton1.set_bg_color(GRISCLAIR);

    /// Bouton 2 qui va être utilise pour effectuer la sauvegarde
    m_top_box.add_child(bouton2);
    bouton2.set_frame(0,80,90,80);//x,y,w,h
    bouton2.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton2);
    Tbouton2.set_frame_pos(25,120);
    Tbouton2.set_message("SAVE");
    Tbouton2.set_bg_color(GRISCLAIR);

    /// Bouton 3 qui va être utilise pour quitter le jeu
    m_top_box.add_child(bouton3);
    bouton3.set_frame(0,160,90,80);//x,y,w,h
    bouton3.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton3);
    Tbouton3.set_frame_pos(25,200);
    Tbouton3.set_message("QUIT");
    Tbouton3.set_bg_color(GRISCLAIR);

    /// Bouton 4 qui va être utilise pour ajouter un sommet dans le graphique
    m_top_box.add_child(bouton4);
    bouton4.set_frame(0,240,90,80);//x,y,w,h
    bouton4.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton4);
    Tbouton4.set_frame_pos(5,280);
    Tbouton4.set_message("ADD VERTEX");
    Tbouton4.set_bg_color(GRISCLAIR);

    /// Bouton 5 qui va être utilise pour ajouter une arete dans le graphique
    m_top_box.add_child(bouton5);
    bouton5.set_frame(0,320,90,80);//x,y,w,h
    bouton5.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton5);
    Tbouton5.set_frame_pos(13,360);
    Tbouton5.set_message("ADD EDGE");
    Tbouton5.set_bg_color(GRISCLAIR);

    /// Bouton 6 qui va être utilise pour supprimer un sommet dans le graphique
    m_top_box.add_child(bouton6);
    bouton6.set_frame(0,400,90,80);//x,y,w,h
    bouton6.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton6);
    Tbouton6.set_frame_pos(5,440);
    Tbouton6.set_message("DEL VERTEX");
    Tbouton6.set_bg_color(GRISCLAIR);

    /// Bouton 7 qui va être utilise pour supprimer une arete dans le graphique
    m_top_box.add_child(bouton7);
    bouton7.set_frame(0,480,90,80);//x,y,w,h
    bouton7.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton7);
    Tbouton7.set_frame_pos(10,520);
    Tbouton7.set_message("DEL EDGE");
    Tbouton7.set_bg_color(GRISCLAIR);

    /// Bouton 8 qui va être utilise pour lla connexite dans le graphique
    m_top_box.add_child(bouton8);
    bouton8.set_frame(0,560,90,80);//x,y,w,h
    bouton8.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton8);
    Tbouton8.set_frame_pos(8,600);
    Tbouton8.set_message("CONNEXITE");
    Tbouton8.set_bg_color(GRISCLAIR);

    /// Bouton 9 qui va être utilise pour l'influence des populations
    m_top_box.add_child(bouton9);
    bouton9.set_frame(0,640,90,80);//x,y,w,h
    bouton9.set_bg_color(GRISCLAIR);

    m_top_box.add_child(Tbouton9);
    Tbouton9.set_frame_pos(8,680);
    Tbouton9.set_message("INFLUENCE");
    Tbouton9.set_bg_color(GRISCLAIR);

    //m_label_ajout_vertex.set_frame(0,0,100,100);//x,y,w,h
    //m_ajout_vertex.set_bg_color(NOIR);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(std::string deuxiemestring)
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton1.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        BITMAP *buffer;
        buffer= create_bitmap(1024,768);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon image sur le buffer
        clear_bitmap(buffer);
        menu_jeu();
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton2.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        sauvegarder(deuxiemestring);
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton3.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        supArete();
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton4.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        addsommet();
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton5.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        addArete();
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton6.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        supSommet();
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton7.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        supArete();
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton8.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        int ordre= m_vertices.size();
        //std::vector<std::vector<int>> adjacence;
        //adjacence=creerMatrice(ordre);
        touteCompoConnexe(ordre);
        //std::cout<<"WIN";
    }

    // Si on clique sur le bouton iindiqué j'appelle la fonction qui est dans le if
    if(m_interface->bouton9.clicked())
    {
        update_values();
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
    m_edges[idx] = Edge(weight, ei);
    ///Correction
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);


    ///Colorier les aretes selon leurs sens
/*
        if(m_signe==0)
        {
            ei->m_top_edge.m_color == VERTCLAIR;
            m_edges[idx].m_signe = 0;

        }
         else if(m_signe==1)
        {
            ei->m_top_edge.m_color == ROUGECLAIR;
            m_edges[idx].m_signe = 1;

        }
         else if(m_signe==2)
        {
            ei->m_top_edge.m_color == BLEUCLAIR;
            m_edges[idx].m_signe = 2;

        }

*/

}


void Graph::test_remove_edge(int eidx)
{
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);
    std::cout << remed.m_interface << std::endl;
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


/// Lecture des fichiers textes selon le chemin que l'on donne
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
        // initialiser et declarer les variables
        std::string lettre =""; //initialiser et declarer la string
        int chiffre=0; //initialiser et declarer l'indice des sommets
        double chiffre2=0; // initialiser et declarer la valeur des sommets
        int chiffre3=0; // initialiser et declarer la coordonnees x des sommets
        int chiffre4=0; //initialiser et declarer la coordonnees y des sommets
        int m_ordre; //initialiser et declarer le nombre de sommet dans le fichier texte

        fp >> m_ordre;
        std::cout << "L'ordre du graphe est : " << m_ordre << std::endl;

        for (int i=0; i<m_ordre; i++)
        {
            std::cout << "i = " << i << std::endl;
            fp >> chiffre; //lecture indice des sommets
            fp >> lettre; // lecture valeur des sommets
            fp >> chiffre2; // lecture coordonnees x des sommets
            fp >> chiffre3; //lecture coordonnees y des sommets
            fp >> chiffre4; //lecture nombre de sommet dans le fichier texte
            std::cout << chiffre << " " << lettre << " " << chiffre2 << " " << chiffre3 << " " << chiffre4 << " " << std::endl; //affichage a la console
            add_interfaced_vertex(chiffre, chiffre2, chiffre3, chiffre4, lettre); // fonction qui ajoute des sommets


        }

        int indice=0; //initialiser et declarer l'indice des sommets
        int sommet1=0; //initialiser et declarer la valeur des sommets
        int sommet2=0; // initialiser et declarer la valeur des sommets
        //int m_signe;
        double poids=0;// initialiser et declarer la valeur de l'arete
        int m_degres; // initialiser et declarer le nombre d'arete

        fp >> m_degres;

        //fp >> m_ordre;
        std::cout << "L'ordre du graphe est : " << m_degres << std::endl;

        for (int j=0; j<m_degres; j++)
        {
            std::cout << "j = " << j << std::endl;
            fp >> indice; //lecture indice des sommets
            fp >> sommet1; //lecture valeur des sommets
            fp >> sommet2; // lecture valeur des sommets
            //fp>> m_signe;
            fp >> poids; // lecture nombre d'arete
            //fp >> chiffre4;
            std::cout << indice << " " << sommet1 << " " << sommet2 << " " << poids << " " << std::endl;
            add_interfaced_edge(indice, sommet1, sommet2, poids); //Fonction qui ajoute des aretes

        }

    }
   /* for(int i=0; i<m_edges.size(); i++)
{
std::cout << m_edges[i].m_signe << std::endl;
}*/
    //Fermeture fichier texte sommet une fois que les donnees sont recuperees
    fp.close();
}


/// Fonction qui ajoute un sommet
void Graph::addsommet()
{

    // Declarer les variables
    std::string nom_sommet;
    double valeur_sommet;
    int cles;

    for (auto &elem : m_edges) // Parcourir la map d'arete
    {
        std::cout << " Cles: " << elem.first << std::endl; //Recuperer la cle dans la map
    }

    //Affichage de la cle de la map
    std::cout << "Entrer une cle disponible: " << std::endl;
    std::cin >> cles;

    // Saisir les variables
    std::cout << "Entrez le nom du sommet: " << std::endl;
    std::cin >> nom_sommet; // Lecture nom sommet
    std::cout << "Entrez la valeur du sommet: " << std::endl;
    std::cin >> valeur_sommet; //Lecture valeur sommet

    // Fonction qui permet l'ajout d'un sommet
    add_interfaced_vertex(cles, valeur_sommet, 125, 10, nom_sommet);

}


/// Fonction qui ajoute une arete entre deux sommets
void Graph::addArete()
{
    // Declarer les variables
    int indice_s1, indice_s2, cles;
    double poids;

    for (auto &elem : m_edges) //Parcourir la map d'aretes
    {
        std::cout << " Cles: " << elem.first << std::endl; //Recuperer la valeur de la cle de la map d'arete
    }

    //Affichage
    std::cout << "Entrer une cle disponible: " << std::endl;
    std::cin >> cles;
    // Saisir les variables
    std::cout << "Entrez l'indice du sommet de depart: " << std::endl;
    std::cin >> indice_s1; // lecture de l'indice du sommet 1 entre par l'utilisateur
    std::cout << "Entrez l'indice du sommet de depart: " << std::endl;
    std::cin >> indice_s2; // lecture de l'indice du sommet 2 entre par l'utilisateur
    std::cout << "Entrez le poids de l'arete: " << std::endl;
    std::cin >> poids; // lecture du poids entre par l'utilisateur


    // Fonction qui permet l'ajout d'une arete entre deux sommets
    add_interfaced_edge(cles, indice_s1, indice_s2, poids);
}

///Fonction qui permet la suppression d'un sommet
void Graph :: supSommet()
{
    int _s = 0;
    // if (mouse_x<=400 && mouse_x>=200 && mouse_b &1 && mouse_y <=100 )
    // {
    std::cout << "Quel sommet voulez-vous supprimer?" << std::endl;
    std::cin >> _s;
    ///Si le sommet existe
    if(m_vertices.count(_s) == 1)
    {
        for(int i = 0; i < m_vertices[_s].m_in.size(); i++)
            this->test_remove_edge(m_vertices[_s].m_in[i]);
        for(int i = 0; i < m_vertices[_s].m_out.size(); i++)
            this->test_remove_edge(m_vertices[_s].m_out[i]);
    }
    m_interface->m_main_box.remove_child( m_vertices[_s].m_interface->m_top_box );
    m_vertices.erase(_s); // effacer sommet
}

/// Fonction qui permet la suppresion d'une arete
void Graph::supArete()
{
    //Declarer les variables
    int indice_s1;
    int indice_s2;
    //int indice_arete;

    //Demander a l'utilisateur les informarions
    std::cout << " Entrer l'indice du sommet de depart: ";
    std::cin >> indice_s1; // lecture de l'indice du sommet 1 entre par l'utilisateur
    std::cout << " Entrer l'indice du sommet d'arrivee: ";
    std::cin >> indice_s2; // lecture de l'indice du sommet 2 entre par l'utilisateur


    if ((m_vertices.count(indice_s1))+(m_vertices.count(indice_s2)) == 2)
    {
        for  (auto &elem : m_edges)
        {
            if (elem.second.m_from == indice_s1 && elem.second.m_to == indice_s2)
            {
                std::cout << "indice sommet suppression: " << elem.first << std::endl;
                test_remove_edge(elem.first);

            }
        }

    }
}

/// Fonction qui permet la sauvegarde d'un grap dans le fichier text
void Graph::sauvegarder(std::string dossier)
{


//sauvegarder la couleur

    // Declarer les variable
    std::string nomfichier = "/fichier.txt";
    std::cout << "on est dans la sauvegarde" << std::endl;
    std::string chemin = dossier + nomfichier;
    std::ofstream nouveau_fichier(chemin, std::ios::out | std::ios::trunc);
    std::cout << "chemin = " << chemin << std::endl;
    // Ouverture d'un nouveau fichier avec remplacement des anciennes donnees par les nouvelles donnees
    if(nouveau_fichier)
    {
        nouveau_fichier << m_vertices.size() << std::endl;
        for(auto &elem : m_vertices)
        {
            std::string name;
            name = elem.second.m_interface->m_img.get_pic_name();
            //name.erase(name.end()-4, name.end());
            //std::cout << m_vertices[i].m_value << " " << name << " " << m_vertices[i].m_interface->m_top_box.get_posx() << " " <<  m_vertices[i].m_interface->m_top_box.get_posy() << " " <<std::endl;
            nouveau_fichier << elem.first << " "<< name <<" "<< elem.second.m_value << " " << elem.second.m_interface->m_top_box.get_posx() << " " << elem.second.m_interface->m_top_box.get_posy() << " " << std::endl;
            //std::cout << "coucou";
        }

        nouveau_fichier << m_edges.size() << std::endl;
        std::cout << "size = " << m_edges.size() << std::endl;
        for(auto &elem : m_edges)
        {
            nouveau_fichier << elem.first << " " << elem.second.m_from << " " << elem.second.m_to << " " << elem.second.m_weight << std::endl;
        }
        nouveau_fichier.close(); //fermeture du nouveau fichier
    }
    else
        std::cout << "Erreur lors de l'enregistrement" << std::endl; // Affichage si erreur lors de l'enregistrement
}

/// Fonction pour trouver une composante fortement connexe
std::vector <int> Graph::uneCompoConnexe(std::vector<std::vector<int>> adjacence, int s, int ordre)
{
    //Variables locales
    std::vector<int>c1;
    std::vector<int>c2;
    std::vector<int>c;
    std::vector<int>marques;
    int x;
    int y;
    int ajoute = 1;

    //allocation de la memoire
    c1.resize(m_vertices.size());
    c2.resize(m_vertices.size());
    c.resize(m_vertices.size());
    marques.resize(m_vertices.size());

    //iniialiser les valeur a 0
    for(int i=0; i<ordre; i++)
    {
        c1.at(i)=0;
        c2.at(i)=0;
        c.at(i)=0;
        marques.at(i)=0;
    }

    //Recherche le sommet s connexe
    c1[s]=1;
    c2[s]=1;

    //Recherche des composantes connexes partant de s a ajouter dans c1
    while(ajoute)
    {
        ajoute = 0;
        for(int x=0; x<ordre; x++)
        {
            if (!marques[x] && c1[x])
            {
                marques[x]=1;

                for (int y=0; y<ordre; y++)
                {
                    if (adjacence[x][y] && !marques[y])
                    {
                        c1[y]=1;
                        ajoute=1;
                    }
                }
            }

        }

        for (x=0; x<ordre; x++)
        {
            c[x]=c1[x]&c2[x];
        }
    }

    //Recherche des composantes connexes partant de s a ajouter dans c2
   ajoute=1;

   for(int i=0; i<ordre; i++)
    {
        marques.at(i)=0;
    }

   while(ajoute)
   {
       ajoute=0;
        for(x=0; x<ordre; x++)
        {
            if (!marques[x] && c2[x])
            {
                marques[x]=1;
                for (y=0; y<ordre; y++)
                {
                    if (adjacence[x][y] && !marques[y])
                    {
                        c2[y]=1;
                        ajoute=1;
                    }
                }
            }
        }
    // Intersection c1 et c2
    for ( x=0; x<ordre; x++)
    {
        c[x]=c1[x] & c2[x];
    }
    }


    return c;
}


/// Fonction pour trouver toutes composantes fortement connexes
std::vector<std::vector<int>> Graph::touteCompoConnexe(int ordre)
{

    std::vector<std::vector<int>> adjacence;
    std::vector<std::vector<int>> tabc;
//    new std::vector<int> ordre;
    std::vector<int> marques;
    int i, j;
    for ( i=0; i<ordre; i++)
    {
        for ( j=0; j<ordre; j++)
        {
            for(auto elem: m_edges)
            {
                if(elem.second.m_from==i && elem.second.m_to==j)
                {
                    adjacence[i][j]= 1;
                }

            }
        }
    }




    //Pour tous sommets x non marques
    //Rechercher composantes fortement connexes de x
    //Marquer chaque sommet x et marquer les sommets y connexes a x et non marques
for (int x=0; x<ordre; x++)
    {
        if(!marques[x])
        {
            std::cout<<"WIN";
            tabc[x]=  uneCompoConnexe(  adjacence, ordre, x);
            marques[x]=1;
            for (int y=0; y<ordre; y++)
            {
                if (tabc[x][y] && !marques[y])
                {
                    marques[y]=1;
                }
            }
        }
    }
    return tabc;
    }


/// Fonction du menu de jeu
std::string Graph::menu_jeu ()
{
    // On declare les variables:
    BITMAP *image1;
    BITMAP *image2;
    BITMAP *buffer;
    bool quitter = false;
    int mouse_prec = 0;
    int mouse_suiv = 0;
    std::string path;

    // On charge les bitmap:
    buffer= create_bitmap(1024,768);
    clear_bitmap(buffer);

    image1= load_bitmap("menu1.jpg", NULL); //chargement bitmap menu1
    image2= load_bitmap("menu2.jpg", NULL); //chargement bitmap menu2

    while(!keypressed()) //Si on presse n'importe quelle touche on passe au menu 2
    {
        blit(image1, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon image sur le buffer
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon buffer sur le screen

    }

    clear_bitmap(buffer);
    // Boucle de jeu
    while(quitter == false)
    {

        blit(image2, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon image sur le buffer
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je met mon screen sur le buffer

       // On parametre la souris
        mouse_prec = mouse_suiv;
        mouse_suiv = mouse_b&1;
        //std::cout << "mouse x " <<mouse_x << std::endl;
        //std::cout << "mouse y " <<mouse_y << std::endl;

        // Jouer
        // Si je me trouve dans les coordonnees du if et que je clique alors je rentre dans la premiere chaine
        if(mouse_suiv && !mouse_prec && (mouse_x>196) && (mouse_x<587) && (mouse_y>59) && (mouse_y<161))
        {
            path = "chaine1";
            quitter = true;
        }

        // Si je me trouve dans les coordonnees du if et que je clique alors je rentre dans la seconde chaine
        if(mouse_suiv && !mouse_prec && (mouse_x>196) && (mouse_x<587) && (mouse_y>229) && (mouse_y<333))
        {
            path = "chaine2";
            quitter = true;
        }

        // Si je me trouve dans les coordonnees du if et que je clique alors je rentre dans la troisieme chaine
        if(mouse_suiv && !mouse_prec && (mouse_x>196) && (mouse_x<587) && (mouse_y>402) && (mouse_y<505))
        {
            path = "chaine3";
            quitter = true;
        }
        // // Si je me trouve dans les coordonnees du if et que je clique alors je quitte le jeu
        if(mouse_suiv && !mouse_prec && (mouse_x>196) && (mouse_x<587) && (mouse_y>559) && (mouse_y<614))
        {
            quitter = true;
            path = "quitter";
        }
    }
    return path;
}


// Fonction qui renvoie la capacité de portage k de l'environnement pour l'espèce de rang i
double Graph :: coeff_k (int i)
{
    double repas = 0;
    for (auto &elem : m_edges)
    {
        //Pour chacune des proies
        if (elem.second.m_to == i)
        {
            int nombre_de_proies = m_vertices[elem.second.m_from].m_value;
            repas += elem.second.m_weight * nombre_de_proies;
        }
    }
    return repas;
}

//Fonction qui envoie la quantité de l'espèce de rang i consommée par les autres espèces
double Graph :: predation(int i)
{
    double pred = 0;
    for (auto &elem : m_edges)
    {
        //Pour chaque prédateur
        if (elem.second.m_from==i)
        {
            int nombre_de_predateurs = m_vertices[elem.second.m_to].m_value;
            pred += elem.second.m_weight * nombre_de_predateurs;
        }
    }
    return pred;
}

//Fonction qui renvoie la population de l'espèce de rang i à la prochaine étape
double Graph :: next_population(int i)
{
    double r = 0.02; //Duree de chaque étape
    double a = 0.05; //Permet d'ajuster le poids de la capacité de portage
    double b = 0.01; //Permet d'ajuster le poids de la prédation

    int n = m_vertices[i].m_value;

    /*
    On n'utilise pas la bonne formule, elle serait plutôt n + r * n * (1 - r / k)
    mais que faire si k = 0 (si une espèce n'a pas de proies)
    */

    double resultat = n + r * (a * coeff_k(i) - b * predation(i));

    //La valeur doit être comprise entre 0 et 100
    return std::max(std::min(resultat,100.0),0.0);
}

//Met le nombre de chaque espèce à jour. Pas tout à fait la bonne procédure, mais
//En pratique on pourra se contenter de faire le calcul  Nt+1 = f (Nt) à tour de rôle pour chaque element
void Graph :: update_values()
{
    for (int i = 0; i < m_vertices.size(); i++)
    {
        m_vertices[i].m_value = next_population(i);
    }
}
