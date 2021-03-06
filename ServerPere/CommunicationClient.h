/*
 * CommunicationClient.h
 *
 *  Created on: 17 janv. 2012
 *      Author: remi
 */

#ifndef COMMUNICATIONCLIENT_H_
#define COMMUNICATIONCLIENT_H_
#include <pthread.h>
#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ServerPere.h"
#include "../Utils/GhomeBox.h"
#include <errno.h>

class CommunicationClient {
public:
	/*
	 * Constructeur
	 */
	CommunicationClient();

	/*
	 * Constructeur
	 */
	CommunicationClient(int a_iSensorServerBox, int a_iActuatorServerBox, int a_iFd, int a_iSock, void * a_pPtr);

	/*
	 * Destructeur
	 */
	virtual ~CommunicationClient();

	/*
	 * Lecture des messages envoyes sur le socket
	 */
	void TransferMessage();

	/*
	 * Lecture d'un message sur le socket pour un nombre d'octets
	 * pass� en param�tre
	 */
	int ReadMessage(int a_iTailleALire);

	/*
	 * Lecture d'un message sur le socket sur un nombre d'octets
	 * passe en param�tre, et definition de la valeur de la r�f�rence
	 * passee en parametre
	 */
	int ReadMessage(int a_TailleALire, int &a_iMessage, string a_sMessage);

private :
	int m_iSensorServerBox;
	int m_iActuatorServerBox;
	int m_iPFileDescriptor;
	bool m_bClientOpened;
	int m_iSocket;
	int m_iId;
	int m_iMetric;
	int m_iRoom;
	int m_iValue;
	int iNbOctets;
	int iTailleALire;
	int iTailleMessage;
};

#endif /* COMMUNICATIONCLIENT_H_ */
