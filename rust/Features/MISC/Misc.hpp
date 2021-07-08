#include "../../SDK/Classes.hpp"
#include "../../Overlay/Menu/Settings.hpp"
#include "../../SDK/BasePlayer.hpp"

namespace Misc {
	void skyDome_Sky()
	{
		uintptr_t m_skyDome = NULL;
		uintptr_t m_camer = NULL;
		uintptr_t last_object = NULL;
		{
			auto tagged_base = Read<uintptr_t>(gBase + 0x08);
			auto tagged_object = Read<uintptr_t>(tagged_base + 0x10);

			while (tagged_object &&
				tagged_object != last_object && (!m_skyDome || !m_camer)) {
				INT16 tag = Read<uintptr_t>(tagged_object + 0x54);

				if (!m_camer) {
					if (tag == 5) {
						uintptr_t objectClass = Read<uintptr_t>(tagged_object + 0x30);

						uintptr_t entity = Read<uintptr_t>(objectClass + 0x18);

						m_camer = Read<uintptr_t>(tagged_object + 0x18);

						pViewMatrix = Read<Matrix4x4>(entity + 0x2E4);

					}
				}

				if (tag == 20011) {

				}

			}
		}
	}
}