/*
 * Reg.h
 *
 *  Created on: May 4, 2013
 *      Author: rburdet
 */

#ifndef REG_H_
#define REG_H_


class Reg {
protected:
	int size;
	int fileAdress;
	int id;

public:
	Reg(int id, int fileAdress);
	int getSize();
	int getId();
	virtual ~Reg();
};

#endif /* REG_H_ */
