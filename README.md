# ft_irc
Project ft_irc de l'ecole 42 Paris

A propos

Ce projet demande de creer un serveur utilisant le protocole IRC (Internet Relay Chat) en C++98.

Le serveur doit pouvoir gerer plusieurs clients simultanement sans problemes mais l’appel system fork() et le mutliprocessing sont interdits.

Nous sommes autorises a utiliser l’appel system poll() mais seulement une fois dans le code.

Nous devons selectonner un client IRC de reference qui sera utilise pour les test.

Le client choisit doit pouvoir se connecter a notre serveur de la meme facon qu’a un serveur IRC officiel.

Voici les fonctionalitees a implementer :

- Pouvoir s’identifier, definir un username, un nickanme.
- Rejoindre un channe
- Pouvoir envoyer et recevoir des messages prives
- la bonne transmission des messages a tous les utilisateurs du channel
- les Operateurs et utilisateurs basiques
- Les commandes suivantes pour les operateurs :
    - KICK : ejecter un client du channel
    - INVITE : inviter un client sur le channel
    - TOPIC : modifier ou afficher le theme du channel
    - MODE :
        - i : Définir/supprimer le canal sur invitation uniquement
        - t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
        - k : Définir/supprimer la clé du canal (mot de passe)
        - o : Donner/retirer le privilège de l’opérateur de channel
        - l : Définir/supprimer la limite d’utilisateurs pour le channel
- BONUS : l’envoi de fichiers
- BONUS : un bot