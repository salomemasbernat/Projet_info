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
    bouton1.set_bg_color(ROSECLAIR);

    m_top_box.add_child(Tbouton1);
    Tbouton1.set_frame_pos(20,40);
    Tbouton1.set_message("RETURN");
    Tbouton1.set_bg_color(ROSECLAIR);

    m_top_box.add_child(bouton2);
    bouton2.set_frame(0,90,90,90);//x,y,w,h
    bouton2.set_bg_color(ROSESOMBRE);

    m_top_box.add_child(Tbouton2);
    Tbouton2.set_frame_pos(25,130);
    Tbouton2.set_message("SAVE");
    Tbouton2.set_bg_color(ROSESOMBRE);

    m_top_box.add_child(bouton3);
    bouton3.set_frame(0,180,90,90);//x,y,w,h
    bouton3.set_bg_color(ROSECLAIR);

    m_top_box.add_child(Tbouton3);
    Tbouton3.set_frame_pos(25,220);
    Tbouton3.set_message("QUIT");
    Tbouton3.set_bg_color(ROSECLAIR);

    m_top_box.add_child(bouton4);
    bouton4.set_frame(0,270,90,90);//x,y,w,h
    bouton4.set_bg_color(ROSESOMBRE);

    m_top_box.add_child(Tbouton4);
    Tbouton4.set_frame_pos(10,310);
    Tbouton4.set_message("ADD VERTEX");
    Tbouton4.set_bg_color(ROSESOMBRE);

    m_top_box.add_child(bouton5);
    bouton5.set_frame(0,360,90,90);//x,y,w,h
    bouton5.set_bg_color(ROSECLAIR);

    m_top_box.add_child(Tbouton5);
    Tbouton5.set_frame_pos(10,400);
    Tbouton5.set_message("ADD EDGE");
    Tbouton5.set_bg_color(ROSECLAIR);

    m_top_box.add_child(bouton6);
    bouton6.set_frame(0,450,90,90);//x,y,w,h
    bouton6.set_bg_color(ROSESOMBRE);

    m_top_box.add_child(Tbouton6);
    Tbouton6.set_frame_pos(5,490);
    Tbouton6.set_message("DEL VERTEX");
    Tbouton6.set_bg_color(ROSESOMBRE);

    m_top_box.add_child(bouton7);
    bouton7.set_frame(0,540,90,90);//x,y,w,h
    bouton7.set_bg_color(ROSECLAIR);

    m_top_box.add_child(Tbouton7);
    Tbouton7.set_frame_pos(10,580);
    Tbouton7.set_message("DEL EDGE");
    Tbouton7.set_bg_color(ROSECLAIR);


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

     if(m_interface->bouton1.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        BITMAP *buffer;
        buffer= create_bitmap(1024,768);
        clear_bitmap(buffer);
        menu_jeu();
        std::cout<<"WIN";
    }

     if(m_interface->bouton2.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        sauvegarder(deuxiemestring);
        std::cout<<"WIN";
    }

     if(m_interface->bouton3.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        supArete();
        std::cout<<"WIN";
    }

     if(m_interface->bouton4.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        addsommet();
        std::cout<<"WIN";
    }

     if(m_interface->bouton5.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        addArete();
        std::cout<<"WIN";
    }

     if(m_interface->bouton6.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        supSommet();
        std::cout<<"WIN";
    }

    if(m_interface->bouton7.clicked()) //m_interface->m_sauvegarde.clicked()
    {
        supArete();
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
    m_edges[idx] = Edge(weight, ei);
    ///Correction
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);

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


// Lecture des fichiers textes:
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


//Fonction qui ajoute un sommet
void Graph::addsommet()
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


// Fonction qui ajoute une arete entre deux sommets
void Graph::addArete()
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
        for(int i = 0; i < m_vertices[_s].m_in.size();i++)
            this->test_remove_edge(m_vertices[_s].m_in[i]);
        for(int i = 0; i < m_vertices[_s].m_out.size();i++)
             this->test_remove_edge(m_vertices[_s].m_out[i]);
    }
    m_interface->m_main_box.remove_child( m_vertices[_s].m_interface->m_top_box );
    m_vertices.erase(_s);
}


void Graph::supArete()
{
    int indice_s1;
    int indice_s2;
    int indice_arete;

    std::cout << " Entrer l'indice du sommet de depart:";
    std::cin >> indice_s1;
    std::cout << " Entrer l'indice du sommet d'arrivee:";
    std::cin >> indice_s2;


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


void Graph::sauvegarder(std::string dossier)
{
  //  std::string nomfichier;
/*    if(path == "chaine1")
        nomfichier = "fichier.txt";
    if(path == "chaine2")
        nomfichier = "fichier.txt";
    if(path == "chaine3")
        nomfichier = "fichier.txt";
*/

    std::string nomfichier = "fichier.txt";
    std::cout << "on est dans la sauvegarde" << std::endl;
    std::string chemin = dossier + nomfichier;
    std::ofstream nouveau_fichier(chemin, std::ios::out | std::ios::trunc);

    if(nouveau_fichier)
    {
        nouveau_fichier << m_vertices.size() << std::endl;
        for(unsigned int i=0 ; i < m_vertices.size() ; i++)
        {
            std::string name;
            name = m_vertices[i].m_interface->m_img.get_pic_name();
            //name.erase(name.end()-4, name.end());
            //std::cout << m_vertices[i].m_value << " " << name << " " << m_vertices[i].m_interface->m_top_box.get_posx() << " " <<  m_vertices[i].m_interface->m_top_box.get_posy() << " " <<std::endl;
            nouveau_fichier << i << " "<< name <<" "<< m_vertices[i].m_value << " " << m_vertices[i].m_interface->m_top_box.get_posx() << " " <<  m_vertices[i].m_interface->m_top_box.get_posy() << " " << std::endl;
            //std::cout << "coucou";
        }

       nouveau_fichier << m_edges.size() << std::endl;
       std::cout << "size = " << m_edges.size() << std::endl;
        for(auto &elem : m_edges)
        {
            nouveau_fichier << elem.first << " " << elem.second.m_from << " " << elem.second.m_to << " " << elem.second.m_weight << std::endl;
        }
        nouveau_fichier.close();
    }
    else
        std::cout << "erreur lors de l'enregistrement" << std::endl;
}


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

    image1= load_bitmap("menu1.jpg", NULL);
    image2= load_bitmap("menu2.jpg", NULL);

    while(!keypressed()) //Si on presse n'importe quelle touche
    {
        blit(image1, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon image sur le buffer
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon buffer sur le screen

    }

    clear_bitmap(buffer);
    // Boucle de jeu
    while(quitter == false)
    {

        blit(image2, buffer, 0, 0, 0, 0, SCREEN_H, SCREEN_W); // je mets mon image sur le buffer

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_H, SCREEN_W);
        mouse_prec = mouse_suiv;
        mouse_suiv = mouse_b&1;
        //std::cout << "mouse x " <<mouse_x << std::endl;
        //std::cout << "mouse y " <<mouse_y << std::endl;

      // Jouer
      if(mouse_suiv && !mouse_prec && (mouse_x>0) && (mouse_x<300) && (mouse_y>0) && (mouse_y<300))
         {

            path = "chaine1";
            quitter = true;
         }

        // Je quitte le jeu
        if(mouse_suiv && !mouse_prec && (mouse_x< 300) && (mouse_x<440) && (mouse_y>240) && (mouse_y<290))
        {
            quitter = true;
            path = "quitter";
        }
    }
    return path;
}
