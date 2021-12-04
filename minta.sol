// A fájl Oláh Bence munkája
// Ezen az okosszerződésen teszteltem először az ESP-vel történő kommunikációt

pragma solidity >=0.8.0 <0.9.0;
contract Data {
	uint256 private price ;
	mapping ( address => uint256 ) private balances ;
	mapping ( address => uint256 ) private quantity ;
	constructor ( uint256 _price ) {
		price = _price ;
	}
	
	function deposit () external payable {
		require (msg . value > 0, " Show me the money !");
		balances [ msg . sender ] += msg . value ;
	}

	function checkBalance () external view returns ( uint256 ) {
		return balances [msg. sender ];
	}

	function checkQuantity () external view returns ( uint256 ) {
		return quantity [msg. sender ];
	}

	function checkQuantity ( address _account ) external view returns
	( uint256 ) {
		return quantity [ _account ];
	}
	
	function register ( uint256 _quantity ) external {
		require ( _quantity * price <= balances [ msg . sender ],
		" Insufficient funds ");
		balances [ msg . sender ] -= _quantity * price ;
		quantity [ msg . sender ] += _quantity ;
	}
}
