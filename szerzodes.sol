pragma solidity >=0.8.0 <0.9.0;
contract Data {
	
	mapping ( address => uint256 ) private penalty ;
	mapping ( address => uint256 ) private correct ;
	mapping ( address => uint256 ) private wallet ;
	mapping ( address => uint256[]) private values;
    uint256 private y = 10 ;
	address provider ;
	
	constructor () {
		provider = msg.sender;
	}
	
	function deposit () external payable {
		require (msg . value > 0, " Show me the money !");
		wallet [ msg . sender ] += msg . value ;
	}
	
	function checkBalance () external view returns ( uint256 ) {
		return wallet [msg. sender ];
	}
	
	function checkPenalty (address _account) external view returns ( uint256 ) {
		return penalty [msg. sender ];
	}
	
	function checkCorrect ( address _account ) external view returns ( uint256 ) {
		return correct [ _account ];
	}
	
	function receiver(uint _value) public {
		if (_value >= 700){
            require (wallet[msg.sender] -y >=0, "Not enough funds");
			wallet[msg.sender] -= y;  // y: a büntetés mértéke
			wallet[provider] += y;
			
			penalty[msg.sender] += 1;
			}
			else{
			correct[msg.sender] +=1;
			}
			
			values[msg.sender].push(_value);
	}
		
	
	function withdraw (uint256 _amount) public {
		require (wallet[msg.sender] >= _amount);
		wallet[msg.sender] -= _amount;
		payable(msg.sender).transfer(_amount);
	}
}