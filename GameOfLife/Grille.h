#include <SFML/Graphics.hpp>
#include <iostream>


class Grille
{

private:

	int taille_grille;
	int espace_inter_ligne_colonne;
	std::vector<std::vector<bool>> cellule;
	std::vector<std::vector<bool>> cellulePrecedente;

public:

	Grille();
	~Grille();
	void draw(sf::RenderWindow &window);
	void move(sf::View &view);
	void zoom(sf::View &view, int &delta);
	void afficherUnivers(sf::RenderWindow &window);
	void clickEtatCellule(sf::RenderWindow &window);
	void startGame(bool & turnFirst);
};