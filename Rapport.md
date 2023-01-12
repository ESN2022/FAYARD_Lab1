<h1>Lab 1 : Led chaser with IOs / interrupts</h1>

Lors de ce premier TP, un chenillard de 8 LEDs à vitesse variable est réalisé par co-design. La cible employée est la DE10-Lite d’Intel.


<h2>I.	Architecture du système</h2>

Le système de co-design comprend le softcore Nios II, de la mémoire de type RAM ainsi que 2 PIOs (Parallel I/O) : le premier pour les sorties, c’est-à-dire les LEDs et le second pour les entrées, c’est-à-dire les boutons. Un module UART est rajouté pour le debug. Le système communique par bus Avalon qui est le bus propriétaire d’Intel. Ce dernier est de type maître/esclave. Il est ici utilisé dans le mode « Memory mapped » c’est-à-dire que chaque périphérique est contrôlé en lisant ou en écrivant à ses adresses. L’ensemble de l’architecture est résumé sur la Figure 1. 

<img width="635" alt="arch_system" src="https://user-images.githubusercontent.com/103188608/212183555-5694193e-892b-42b0-854a-d169dd854579.png">

Sur cette figure, on remarque que le PIO des entrées peut être relié par le bus Avalon et donc le mode de fonctionnement sera du polling ou par une ligne d’interruption et ainsi être réactif dès le changement d’état de l’entrée. 


<h2>II.	Progression et résultat</h2>

Dans un premier temps, le système réalisé est un chenillard de 8 LEDs et correspond au premier commit sur GitHub.

Le second commit correspond au rajout du contrôle de la vitesse par les slide buttons en mode polling. Le programme C a été écrit de manière à ne gérer qu’un seul slide button actif à la fois. Une situation par défaut est également présente et permet de donner la vitesse dans le cas où aucun des slides buttons n’est actif. 

Le troisième commit correspond à l’ajout d’un bouton poussoir pour démarrer le chenillard. Il faut ici être vigilant car les boutons poussoirs sont actifs à l’état bas. 

Le quatrième commit fait en sorte que l’appuie sur le bouton poussoir permette de démarrer puis d’éteindre quand on le souhaite. Cependant, il est important de noter que, étant en mode polling, le bouton doit être appuyé au bon moment. 

Le cinquième commit ajoute une interruption sur les slide buttons. Il faut ici prendre garde à bien remettre à zéro l’interruption à la fin de celle-ci.

Voici le résultat final :

https://user-images.githubusercontent.com/103188608/212183736-e20ea339-4a58-4950-ba00-55f994b798b0.mov


<h2>Conclusion</h2>

Ce TP a été l’occasion de bien comprendre l’ensemble du flow de co-design avec un FPGA et un Nios II. Il a également permis de mettre en place des IP très régulièrement utilisée tel que des boutons, des LEDs ou encore des interruptions. Un des points clés est également la familiarisation avec les fonctions HAL.

Les difficultés principales rencontrées lors de ce premier TP sont résumées via les points de vigilances suivants :
-	Lors de la création du projet, ne pas choisir la board sous peine d’avoir déjà des programmes VHDL et des pins assignées.
-	Penser à retrouver les états actifs des périphériques.


