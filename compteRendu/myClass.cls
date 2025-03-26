\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{myClass}

\LoadClass[a4paper,11pt]{article}

\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[french]{babel}
\RequirePackage{bookmark}
\RequirePackage{lipsum}
\RequirePackage{graphicx}
\RequirePackage{float}
\RequirePackage{tikz}
\RequirePackage{listings}
\RequirePackage{xcolor}
\RequirePackage{tocloft}
\RequirePackage{geometry}
\RequirePackage{fancyhdr}
\RequirePackage{hyperref}
\RequirePackage{tabularx}
\RequirePackage{enumitem}
\RequirePackage{amsmath}
\RequirePackage{algorithm}
\RequirePackage{algpseudocode}
\RequirePackage{csquotes}
\RequirePackage{titlesec}
\RequirePackage{fbox}
\RequirePackage{multicol}
\usetikzlibrary{shadows}
\RequirePackage{wrapfig}



% regler les erreurs de compilation 
\setlength{\headheight}{37.76534pt}
\addtolength{\topmargin}{-22.76534pt}

% Customiser le header
\pagestyle{fancy}
\fancyhf{}
\lhead{\includegraphics[width=2cm]{images/2020_UNICAEN_LOGO_isotype-signature_horizontal_noir.png}}
\chead{\rightmark}
\cfoot{\thepage}

% importer du code
\lstset{language=Java,captionpos=b,tabsize=3,frame=lines,keywordstyle=\color{blue},commentstyle=\color{green},stringstyle=\color{red},numbers=left,numberstyle=\tiny,numbersep=5pt,breaklines=true,showstringspaces=false,basicstyle=\footnotesize,emph={label}}

\newcommand{\scalefactor}{0.5}

\tikzset{
    basic/.style  = {draw, text width=2cm, font=\sffamily, rectangle},
    root/.style   = {basic, rounded corners=2pt, thin, align=center, fill=green!30, drop shadow},
    level 2/.style = {basic, rounded corners=6pt, thin,align=center, fill=green!60, text width=6em, drop shadow}, % Decrease text width here
    level 3/.style = {basic, thin, align=left, fill=pink!60, text width=5em, drop shadow} % Decrease text width here
}

\makeatletter
\renewcommand{\maketitle}{
  \begin{center}
    {\Huge\bfseries \@title}\\
    \vspace{1em}
    {\Large\@author}\\
    \vspace{1em}
    {\@date}
  \end{center}
}
\makeatother