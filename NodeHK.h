#include "HanhKhach.h"


class NodeHK{
	public:
		HanhKhach hk;
		NodeHK* left;
		NodeHK* right;
		
		NodeHK(){
			left = NULL;
			right = NULL;
		}
		
		NodeHK(HanhKhach newHK, NodeHK* left = NULL, NodeHK* right = NULL){
			hk = newHK;
			this->left = left;
			this->right = right;
		}
};
