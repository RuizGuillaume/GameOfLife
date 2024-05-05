#include "Grille.h"

Grille::Grille()
{
	taille_grille = 50;
	espace_inter_ligne_colonne = 900 / taille_grille;

	std::vector<bool> m_v;

	for (int i = 0; i < taille_grille; i++)
	{
		for (int j = 0; j < taille_grille; j++)
		{
			m_v.push_back(0);
		}
		cellule.push_back(m_v);
		cellulePrecedente.push_back(m_v);
	}

	for (int i = 0; i < taille_grille; i++)
	{
		for (int j = 0; j < taille_grille; j++)
		{
			cellule[i][j] = 0;
			cellulePrecedente[i][j] = 0;
		}
	}
}

Grille::~Grille()
{
}

void Grille::move(sf::View &view)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		view.move(-30, 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		view.move(30, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		view.move(0, -30);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		view.move(0, 30);
	}
}

void Grille::zoom(sf::View &view, int &delta)
{
	if (delta < 0)
		view.zoom(1.2f);

	if (delta > 0)
		view.zoom(0.8f);
}

void Grille::afficherUnivers(sf::RenderWindow &window)
{
	sf::RectangleShape ligneH(sf::Vector2f(901, 1)); ligneH.setPosition(-1, -1); window.draw(ligneH);
	sf::RectangleShape ligneB(sf::Vector2f(902, 1)); ligneB.setPosition(-1, 900); window.draw(ligneB);
	sf::RectangleShape ligneG(sf::Vector2f(1, 901)); ligneG.setPosition(-1, -1); window.draw(ligneG);
	sf::RectangleShape ligneD(sf::Vector2f(1, 902)); ligneD.setPosition(900, -1); window.draw(ligneD);
}

void Grille::clickEtatCellule(sf::RenderWindow &window)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f mousePositionGlobal = window.mapPixelToCoords(MousePosition);

		if (mousePositionGlobal.x > 0 && 
			mousePositionGlobal.y > 0 && 
			mousePositionGlobal.x < espace_inter_ligne_colonne*taille_grille &&
			mousePositionGlobal.y < espace_inter_ligne_colonne*taille_grille)
		{
			sf::Vector2i celluleVie;

			celluleVie = sf::Vector2i((mousePositionGlobal.x) / espace_inter_ligne_colonne, (mousePositionGlobal.y) / espace_inter_ligne_colonne);

			if (cellule[celluleVie.x][celluleVie.y] == 0)
				cellule[celluleVie.x][celluleVie.y] = 1;
		}

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i MousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f mousePositionGlobal = window.mapPixelToCoords(MousePosition);

		if (mousePositionGlobal.x > 0 && 
			mousePositionGlobal.y > 0 &&
			mousePositionGlobal.x < espace_inter_ligne_colonne*taille_grille && 
			mousePositionGlobal.y < espace_inter_ligne_colonne*taille_grille)
		{
			sf::Vector2i celluleVie;

			celluleVie = sf::Vector2i((mousePositionGlobal.x) / espace_inter_ligne_colonne, (mousePositionGlobal.y) / espace_inter_ligne_colonne);

			if (cellule[celluleVie.x][celluleVie.y] == 1)
				cellule[celluleVie.x][celluleVie.y] = 0;
		}
	}
}

void Grille::startGame(bool & firstTurn)
{

	//INITIALISATION DE LA GRILLE SECONDAIRE 
	if (firstTurn = 1)
	{
		for (int i = 1; i < taille_grille - 1; i++)
		{
			for (int j = 1; j < taille_grille - 1; j++)
			{
				cellulePrecedente[i][j] = cellule[i][j];
			}
		}
		firstTurn = 0;
	}

	//CALCUL DU NOMBRE DE VOISINS
	for (int i = 1; i < taille_grille - 1; i++)
	{
		for (int j = 1; j < taille_grille - 1; j++)
		{
			int nombreVoisins = cellulePrecedente[i - 1][j + 1] + cellulePrecedente[i - 1][j] + 
								cellulePrecedente[i - 1][j - 1] + cellulePrecedente[i][j + 1] + 
								cellulePrecedente[i][j - 1] + cellulePrecedente[i + 1][j + 1] + 
								cellulePrecedente[i + 1][j] + cellulePrecedente[i + 1][j - 1];

			if (cellule[i][j] == 0 && nombreVoisins == 3)
				cellule[i][j] = 1;

			if (cellule[i][j] == 1 && (nombreVoisins < 2 || nombreVoisins > 3))
				cellule[i][j] = 0;

		}
	}

	for (int i = 1; i < taille_grille - 1; i++)
	{
		for (int j = 1; j < taille_grille - 1; j++)
		{
			cellulePrecedente[i][j] = cellule[i][j];
		}
	}
}

void Grille::draw(sf::RenderWindow & window)
{

	for (int i = 0; i < taille_grille; i++)
	{
		for (int j = 0; j < taille_grille; j++)
		{
			if (cellule[i][j] == 1)
			{
				sf::RectangleShape celluleVivante(sf::Vector2f(espace_inter_ligne_colonne, espace_inter_ligne_colonne));
				celluleVivante.setPosition(espace_inter_ligne_colonne*i, espace_inter_ligne_colonne*j);
				window.draw(celluleVivante);
			}
			else
			{
				sf::RectangleShape celluleMorte(sf::Vector2f(espace_inter_ligne_colonne, espace_inter_ligne_colonne));
				celluleMorte.setPosition(espace_inter_ligne_colonne*i, espace_inter_ligne_colonne*j);
				celluleMorte.setFillColor(sf::Color::Black);
				window.draw(celluleMorte);
			}
		}
	}
}
