#include "pch.h"

#include "SbsFile.h"

namespace sbsmanip {

Sector SbsFile::sector() {
	return root().child("MyObjectBuilder_Sector");
}

} // namespace sbsmanip