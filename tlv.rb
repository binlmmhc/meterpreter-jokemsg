# -*- coding: binary -*-
module Rex
module Post
module Meterpreter
module Extensions
module Jokemsg

TLV_TYPE_JOKEMSG_MESSAGE		= TLV_META_TYPE_STRING 	| (TLV_EXTENSIONS + 1)
TLV_TYPE_JOKEMSG_RESULT			= TLV_META_TYPE_BOOL	| (TLV_EXTENSIONS + 2)

end
end
end
end
end