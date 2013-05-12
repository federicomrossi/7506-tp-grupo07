/*
 * BlockTable.h
 *
 *  Created on: May 11, 2013
 *      Author: rburdet
 */

#ifndef BLOCKTABLE_H_
#define BLOCKTABLE_H_

class BlockTable {
public:
	BlockTable();
	virtual ~BlockTable();
	int insert(Block& aBlock);

protected:
	int size;
	int blockReferences[];
};

#endif /* BLOCKTABLE_H_ */
