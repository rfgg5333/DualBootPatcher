/*
 * Copyright (C) 2015  Andrew Gunnerson <andrewgunnerson@gmail.com>
 *
 * This file is part of MultiBootPatcher
 *
 * MultiBootPatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MultiBootPatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MultiBootPatcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ramdiskpatchers/hllte.h"

#include <regex>

#include "patcherconfig.h"
#include "ramdiskpatchers/core.h"


namespace mbp
{

/*! \cond INTERNAL */
class HllteBaseRP::Impl
{
public:
    const PatcherConfig *pc;
    const FileInfo *info;
    CpioFile *cpio;

    PatcherError error;
};
/*! \endcond */


/*!
    \class HllteRP
    \brief Handles common ramdisk patching operations for the Samsung Galaxy Note 3 Neo

    This patcher handles the patching of ramdisks for the Samsung Galaxy Note 3 Neo.
    Starting from version 9.0.0, every Android ramdisk is supported.
 */


HllteBaseRP::HllteBaseRP(const PatcherConfig * const pc,
                         const FileInfo * const info,
                         CpioFile * const cpio) :
    m_impl(new Impl())
{
    m_impl->pc = pc;
    m_impl->info = info;
    m_impl->cpio = cpio;
}

HllteBaseRP::~HllteBaseRP()
{
}

PatcherError HllteBaseRP::error() const
{
    return m_impl->error;
}

////////////////////////////////////////////////////////////////////////////////

const std::string HllteDefaultRP::Id = "hllte/default";

HllteDefaultRP::HllteDefaultRP(const PatcherConfig * const pc,
                               const FileInfo *const info,
                               CpioFile *const cpio)
    : HllteBaseRP(pc, info, cpio)
{
}

std::string HllteDefaultRP::id() const
{
    return Id;
}

bool HllteDefaultRP::patchRamdisk()
{
    CoreRP corePatcher(m_impl->pc, m_impl->info, m_impl->cpio);

    if (!corePatcher.patchRamdisk()) {
        m_impl->error = corePatcher.error();
        return false;
    }

    if (!corePatcher.fixChargerMountAuto()) {
        m_impl->error = corePatcher.error();
        return false;
    }

    return true;
}

}
