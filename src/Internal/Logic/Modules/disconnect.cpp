#include "Game/MatchUtil.h"
#include "Game/Limit.h"
#include <cstdint>

namespace Modules {
	void disconnect() {
		//if (Lp::Net::MatchingSeqBase::getConnectedNum() > -1) {
			//Lp::Utl::Limit::tryCloseJointSessionWithoutSeq();
			//Lp::Utl::Limit::closeParticipationWithoutSeq();
		uint32_t err = 5;
		//Lp::Utl::Limit::setNetworkErrorForAppSession(&err);
		//}
	}
}
