# -*- coding: binary -*-
require 'rex/post/meterpreter'

module Rex
module Post
module Meterpreter
module Ui

###
#
# Jokemsg extension user interface.
#
###
class Console::CommandDispatcher::Jokemsg

  Klass = Console::CommandDispatcher::Jokemsg

  include Console::CommandDispatcher

  #
  # Initializes an instance of the jokemsg command interaction.
  #
  def initialize(shell)
    super
  end

  #
  # List of supported commands.
  #
  def commands
    {
      "doingjoke" =>  "joke others with a message box  dialog",
    }
  end

  def cmd_doingjoke(msg)
    jokemsg_ret = client.jokemsg.jokemsg_doingjoke(msg)
    return jokemsg_ret
  end

  #
  # Name for this dispatcher
  #
  def name
    "Jokemsg"
  end

end

end
end
end
end
