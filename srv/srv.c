#include "../lib/standard.h"

int main(){
    
    return 0;
}

void serveur(void){
    message_t buff;	
	int se /* écoute */, sd /* dialogue */;
	socklen_t lenClt;
	struct sockaddr_un mySockName, clt;
	
	// Déclaration & création d'une socket UNIX en mode DGRAM
	CHECK(se = socket(PF_UNIX, SOCK_STREAM, 0), "socket 1");
	printf("N° de canal créé pour la socket %d\n", se);
	
	//préparation de l'adressage de la socket
	mySockName.sun_family = PF_UNIX;
	strcpy(mySockName.sun_path, "./sokUnix");
	// Association la socket avec son adresse
	CHECK(bind(se, (struct sockaddr *)&mySockName, sizeof(mySockName)),"bind serveur");
	while (1) { // Boucle infinie : attente requête / traitement de la requête
		// attente de connexion : accept()
		lenClt = sizeof(clt);
		CHECK(sd=accept(se, (struct sockaddr *)&clt, &lenClt),"accept client");
		memset(&buff, MAX_BUFF, (0));
		printf("Attente de réception d'un message\n");
		CHECK (recv(sd, buff, MAX_BUFF, 0), "recv");
		printf("\tMessage reçu : ##%s## sur le canal %d\n", buff, sd);
		printf("\tpar le canal client : ##%s##\n\n", clt.sun_path);
		close(sd);
	}

	// fermeture de la socket
	close(se);
	// suppresion de la socket
	unlink(mySockName.sun_path);
}