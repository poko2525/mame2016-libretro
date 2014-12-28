/**********************************************************************

    Sega Game Gear "Gear to Gear Port" emulation

    Copyright MESS Team.
    Visit http://mamedev.org for licensing and usage restrictions.

**********************************************************************/

#include "gear2gear.h"
// slot devices
#include "smsctrladp.h"



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

const device_type GG_GEAR2GEAR_PORT = &device_creator<gg_gear2gear_port_device>;



//**************************************************************************
//  CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_gg_gear2gear_port_interface - constructor
//-------------------------------------------------

device_gg_gear2gear_port_interface::device_gg_gear2gear_port_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig,device)
{
	m_port = dynamic_cast<gg_gear2gear_port_device *>(device.owner());
}


//-------------------------------------------------
//  ~device_gg_gear2gear_port_interface - destructor
//-------------------------------------------------

device_gg_gear2gear_port_interface::~device_gg_gear2gear_port_interface()
{
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  gg_gear2gear_port_device - constructor
//-------------------------------------------------

gg_gear2gear_port_device::gg_gear2gear_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
						device_t(mconfig, GG_GEAR2GEAR_PORT, "Gear to Gear Port", tag, owner, clock, "gg_gear2gear_port", __FILE__),
						device_slot_interface(mconfig, *this),
						m_th_pin_handler(*this),
						m_pixel_handler(*this)
{
}


//-------------------------------------------------
//  gg_gear2gear_port_device - destructor
//-------------------------------------------------

gg_gear2gear_port_device::~gg_gear2gear_port_device()
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void gg_gear2gear_port_device::device_start()
{
	m_device = dynamic_cast<device_gg_gear2gear_port_interface *>(get_card_device());

	m_th_pin_handler.resolve_safe();
	m_pixel_handler.resolve_safe(0);
}


UINT8 gg_gear2gear_port_device::port_r()
{
	UINT8 data = 0xff;
	if (m_device)
		data = m_device->peripheral_r();
	return data;
}

void gg_gear2gear_port_device::port_w( UINT8 data )
{
	if (m_device)
		m_device->peripheral_w(data);
}


void gg_gear2gear_port_device::th_pin_w(int state)
{
	m_th_pin_handler(state);
}

UINT32 gg_gear2gear_port_device::pixel_r()
{
	return m_pixel_handler();
}


//-------------------------------------------------
//  SLOT_INTERFACE( gg_gear2gear_port_devices )
//-------------------------------------------------

SLOT_INTERFACE_START( gg_gear2gear_port_devices )
	SLOT_INTERFACE("smsctrladp", SMS_CTRL_ADAPTOR)
SLOT_INTERFACE_END
