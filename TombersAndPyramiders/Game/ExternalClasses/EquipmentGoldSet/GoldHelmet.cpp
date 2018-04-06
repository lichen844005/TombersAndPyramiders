/*===================================================================================*//**
	GoldHelmet
	
	A weak gold helmet.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "GoldHelmet.h"

/*----------------------------------------------------------------------------------------
	Class Fields
----------------------------------------------------------------------------------------*/
const float GoldHelmet::GOLD_HELMET_CRITICAL_RESIST_CHANCE = 0.05f;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
GoldHelmet::GoldHelmet() :
	BaseHelmet{ GOLD_HELMET_CRITICAL_RESIST_CHANCE }
{}
