#pragma once

// win10 or later
#define _WIN32_WINNT 0x0A00  // D�finit la version minimale de Windows (Windows 10)
#include <sdkddkver.h>  // Inclut les d�finitions de versions Windows

#define WIN32_LEAN_AND_MEAN  // Exclut les API Windows rarement utilis�es pour acc�l�rer la compilation

// D�sactive certaines fonctionnalit�s des en-t�tes Windows pour r�duire la taille du programme
#define NOGDICAPMASKS        // Exclut les constantes de masques de capacit� GDI
#define NOSYSMETRICS         // Exclut les constantes de mesures syst�me
#define NOMENUS              // Exclut les d�finitions de menus
#define NOICONS              // Exclut les d�finitions d'ic�nes
#define NOSYSCOMMANDS        // Exclut les d�finitions de commandes syst�me
#define NORASTEROPS          // Exclut les op�rations raster GDI inutiles
#define OEMRESOURCE          // Exclut les ressources OEM
#define NOATOM               // Exclut les fonctions Atom (gestion de cha�nes courtes globales)
#define NOCLIPBOARD          // Exclut les API du presse-papiers
#define NOCOLOR              // Exclut les constantes de couleur
#define NOCTLMGR             // Exclut les contr�les standards de Windows (boutons, listes, etc.)
#define NODRAWTEXT           // Exclut DrawText et ses constantes associ�es
#define NOKERNEL             // Exclut certaines fonctions du noyau Windows
#define NONLS                // Exclut les fonctions de support des langues natives (NLS)
#define NOMEMMGR             // Exclut les fonctions de gestion de m�moire
#define NOMETAFILE           // Exclut les d�finitions de m�tafichiers GDI
#define NOOPENFILE           // Exclut les anciennes fonctions de gestion de fichiers (remplac�es par CreateFile, etc.)
#define NOSCROLL             // Exclut les constantes de barres de d�filement
#define NOSERVICE            // Exclut les services Windows
#define NOSOUND              // Exclut les fonctions de gestion du son
#define NOTEXTMETRIC         // Exclut les constantes li�es aux m�triques de texte
#define NOWH                 // Exclut les hooks Windows
#define NOCOMM               // Exclut les API de communication s�rie
#define NOKANJI              // Exclut le support des caract�res Kanji
#define NOHELP               // Exclut l'API d'aide Windows
#define NOPROFILER           // Exclut les fonctions de profilage
#define NODEFERWINDOWPOS     // Exclut DeferWindowPos et ses fonctions associ�es
#define NOMCX                // Exclut les contr�les de biblioth�que d'extension Microsoft (MCX)
#define NORPC                // Exclut les fonctions d'appel de proc�dure distante (RPC)
#define NOPROXYSTUB          // Exclut les proxys et stubs RPC
#define NOIMAGE              // Exclut les constantes li�es aux images Windows
#define NOTAPE               // Exclut les fonctions de gestion de bandes magn�tiques

#define NOMINMAX  // D�sactive les macros min() et max() de Windows pour �viter les conflits avec la STL

#define STRICT  // Active une v�rification stricte des types pour les API Windows

#include <Windows.h>  // Inclut l'en-t�te principal de l'API Windows
