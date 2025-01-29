#pragma once

// win10 or later
#define _WIN32_WINNT 0x0A00  // Définit la version minimale de Windows (Windows 10)
#include <sdkddkver.h>  // Inclut les définitions de versions Windows

#define WIN32_LEAN_AND_MEAN  // Exclut les API Windows rarement utilisées pour accélérer la compilation

// Désactive certaines fonctionnalités des en-têtes Windows pour réduire la taille du programme
#define NOGDICAPMASKS        // Exclut les constantes de masques de capacité GDI
#define NOSYSMETRICS         // Exclut les constantes de mesures système
#define NOMENUS              // Exclut les définitions de menus
#define NOICONS              // Exclut les définitions d'icônes
#define NOSYSCOMMANDS        // Exclut les définitions de commandes système
#define NORASTEROPS          // Exclut les opérations raster GDI inutiles
#define OEMRESOURCE          // Exclut les ressources OEM
#define NOATOM               // Exclut les fonctions Atom (gestion de chaînes courtes globales)
#define NOCLIPBOARD          // Exclut les API du presse-papiers
#define NOCOLOR              // Exclut les constantes de couleur
#define NOCTLMGR             // Exclut les contrôles standards de Windows (boutons, listes, etc.)
#define NODRAWTEXT           // Exclut DrawText et ses constantes associées
#define NOKERNEL             // Exclut certaines fonctions du noyau Windows
#define NONLS                // Exclut les fonctions de support des langues natives (NLS)
#define NOMEMMGR             // Exclut les fonctions de gestion de mémoire
#define NOMETAFILE           // Exclut les définitions de métafichiers GDI
#define NOOPENFILE           // Exclut les anciennes fonctions de gestion de fichiers (remplacées par CreateFile, etc.)
#define NOSCROLL             // Exclut les constantes de barres de défilement
#define NOSERVICE            // Exclut les services Windows
#define NOSOUND              // Exclut les fonctions de gestion du son
#define NOTEXTMETRIC         // Exclut les constantes liées aux métriques de texte
#define NOWH                 // Exclut les hooks Windows
#define NOCOMM               // Exclut les API de communication série
#define NOKANJI              // Exclut le support des caractères Kanji
#define NOHELP               // Exclut l'API d'aide Windows
#define NOPROFILER           // Exclut les fonctions de profilage
#define NODEFERWINDOWPOS     // Exclut DeferWindowPos et ses fonctions associées
#define NOMCX                // Exclut les contrôles de bibliothèque d'extension Microsoft (MCX)
#define NORPC                // Exclut les fonctions d'appel de procédure distante (RPC)
#define NOPROXYSTUB          // Exclut les proxys et stubs RPC
#define NOIMAGE              // Exclut les constantes liées aux images Windows
#define NOTAPE               // Exclut les fonctions de gestion de bandes magnétiques

#define NOMINMAX  // Désactive les macros min() et max() de Windows pour éviter les conflits avec la STL

#define STRICT  // Active une vérification stricte des types pour les API Windows

#include <Windows.h>  // Inclut l'en-tête principal de l'API Windows
