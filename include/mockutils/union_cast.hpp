/*
 * Copyright (c) 2014 Eran Pe'er.
 *
 * This program is made available under the terms of the MIT License.
 *
 * Created on Mar 10, 2014
 */

#ifndef union_cast_h__
#define union_cast_h__

namespace fakeit {

template<typename TARGET, typename SOURCE>
TARGET union_cast(SOURCE source) {
	//static_assert(sizeof(TARGET) == sizeof(SOURCE), "can't convert");
	union {
		SOURCE source;
		TARGET target;
	} u;
	u.source = source;
	return u.target;
}

}
#endif // union_cast_h__
