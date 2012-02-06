/*
 * communicationclient.cpp
 *
 *  Created on: 17 janv. 2012
 *      Author: remi
 */

#include "CommunicationClient.h"
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

ServerPere* papa;

CommunicationClient::CommunicationClient()
/*
 * Constructeur
 */
{


}

CommunicationClient::CommunicationClient(int a_iSensorServerBox, int a_iActuatorServerBox, int a_iFd, int a_iSock, void * a_pPtr) :
m_iSensorServerBox(a_iSensorServerBox), m_iActuatorServerBox(a_iActuatorServerBox), m_iPFileDescriptor(a_iFd), m_iSocket(a_iSock)
/*
 * Constructeur surcharge.
 * Appel la methode de gestion des messages lues sur le socket
 */
{
	papa = (ServerPere*)a_pPtr;
	CommunicationClient::TransferMessage();

}

CommunicationClient::~CommunicationClient()
/*
 * Destructeur
 */
{

}

void CommunicationClient::FreeCreateBuffer(int a_iLongueur)
/*
 * Prends en parametre la longueur du m_cBuffer à initialisé,
 * après sa liberation memoire.
 */
{
	free(m_cBuffer);
	m_cBuffer = (char*) malloc(a_iLongueur);
	bzero(m_cBuffer,a_iLongueur);
}

void CommunicationClient::TransferMessage()
/*
 * Gere les messages recues sur le socket (envoyes par les clients).
 * Fonctionnement d'une lecture d'un ordre de pilotage
	    * d'un client :
	    * - lecture sur un octet : type du message (info, pilotage,...)
	    * 		- id = 0 : deconnexion du client
	    * 		- id = 4 : ordre de fermeture du server
	    * 		- id = 1 : info
	    * 		- id = 2 : pilotage
	    * 		- id = 3 : ordre de maintenance
	    * - lecture sur un octet : taille du message de metric
	    * - lecture du metric
	    * - lecture sur un octer : taille du message de room
	    * - lecture du room
	    * - lecture sur un octet : taille du message de value
 */
{

	   int n;
	   m_bClientOpened=true;
	   int iTailleALire = 1;
	   int iTailleMessage;
while(m_bClientOpened)
{
	CommunicationClient::FreeCreateBuffer(iTailleALire);
	n=read(m_iPFileDescriptor, m_cBuffer, iTailleALire);
	m_iId=atoi(m_cBuffer);
	CommunicationClient::FreeCreateBuffer(iTailleALire);
	switch(m_iId){
	case 4 :
		m_bClientOpened=false;
		papa->set_opened(false);
		papa->kill_thread();
		break;
	case 0 :
		m_bClientOpened=false;
		papa->delete_fd(m_iPFileDescriptor);
		break;
	case 1 :
		break;
	case 2 :
		n = read(m_iPFileDescriptor, m_cBuffer, iTailleALire);
		iTailleMessage = atoi(m_cBuffer);
		CommunicationClient::FreeCreateBuffer(iTailleMessage);
		//Lecture de metric
		n = read(m_iPFileDescriptor, m_cBuffer, iTailleMessage);
		m_iMetric = atoi(m_cBuffer);
		CommunicationClient::FreeCreateBuffer(iTailleALire);
		//Nombre d'octets pour room
		n = read(m_iPFileDescriptor, m_cBuffer, iTailleALire);
		iTailleMessage = atoi(m_cBuffer);
		CommunicationClient::FreeCreateBuffer(iTailleMessage);
		//Lecture de room
		n = read(m_iPFileDescriptor, m_cBuffer, iTailleMessage);
		m_iRoom = atoi(m_cBuffer);
		CommunicationClient::FreeCreateBuffer(iTailleALire);
		//Nombre d'octets pour value
		n = read(m_iPFileDescriptor, m_cBuffer, iTailleALire);
		iTailleMessage = atoi(m_cBuffer);
		CommunicationClient::FreeCreateBuffer(iTailleMessage);
		//Lecture de value
		n = read(m_iPFileDescriptor, m_cBuffer, iTailleMessage);
		m_iValue = atoi(m_cBuffer);

		//Ecriture du message dans la boite aux lettres actuator
		GhomeBox::send_actuator_box(m_iActuatorServerBox, m_iId, m_iMetric, m_iRoom, m_iValue);

		break;
	case 3 :
		break;

	}




}

}
