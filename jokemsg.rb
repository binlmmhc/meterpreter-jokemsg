# -*- coding: binary -*-

require 'rex/post/meterpreter/extensions/jokemsg/tlv'

module Rex
module Post
module Meterpreter
module Extensions
module Jokemsg

###
#this meterpreter extension is a test extension
###
class Jokemsg < Extension

	def initialize(client)
		super(client, "jokemsg")

		client.register_extension_aliases(
			[
				{
					'name'	=>	"jokemsg",
					'ext'	=>	self
				},
			])
	end

	def jokemsg_doingjoke(joke_msg)
		request = Packet.create_request("jokemsg_doingjoke")
		request.add_tlv(TLV_TYPE_JOKEMSG_MESSAGE, joke_msg)

		response = client.send_request(request)

		return{
			"jokemsg_ret"	=>	response.get_tlv_value(TLV_TYPE_JOKEMSG_RESULT)
		}
	end
end
end; end; end; end; end
