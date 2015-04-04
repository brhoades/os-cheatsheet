/*******************************************
 * Student:    Billy J Rhoades II
 * Username:   bjrq48
 * Class:      CS5201
 * Assignment: 2 
 * File:       program.cpp
 ******************************************/
#include "program.h"

Program::Program( ) { }

Program::Program( const unsigned int num, const unsigned pageNum, const unsigned int numPages )
{
  m_num = num;
  m_numPages = numPages;
  m_firstPage = pageNum;

  for( unsigned int i=pageNum; i<pageNum+numPages; i++ )
    m_jump[i] = -1;
}

Program& Program::operator=( const Program& rhs )
{
  m_firstPage = rhs.m_firstPage;
  m_numPages = rhs.m_numPages;
  m_num = rhs.m_num; 

  m_jump = rhs.m_jump;

  return *this;
}

Program::~Program( )
{
}
