/*
 * terrainmodel.h
 * Copyright 2008-2012, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright 2009, Edward Hutchins <eah1@yahoo.com>
 * Copyright 2012, Manu Evans <turkeyman@gmail.com>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TERRAINMODEL_H
#define TERRAINMODEL_H

#include <QAbstractItemModel>
#include <tileset.h>

namespace Tiled {

class Tileset;
class Terrain;

namespace Internal {

class MapDocument;

/**
 * A model providing a tree view on the terrain types available on a map.
 */
class TerrainModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum UserRoles {
        TerrainRole = Qt::UserRole
    };

    /**
     * Constructor.
     *
     * @param mapDocument the map to manage terrains for
     */
    TerrainModel(MapDocument *mapDocument,
                 QObject *parent = nullptr);

    ~TerrainModel();

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex index(Tileset *tileset) const;
    QModelIndex index(Terrain *terrain) const;

    QModelIndex parent(const QModelIndex &child) const override;

    /**
     * Returns the number of rows. For the root, this is the number of tilesets
     * with terrain types defined. Otherwise it is the number of terrain types
     * in a certain tileset.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Returns the number of columns.
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Returns the data stored under the given <i>role</i> for the item
     * referred to by the <i>index</i>.
     */
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    /**
     * Returns the tileset at the given \a index, or 0 if there is no tileset.
     */
    Tileset *tilesetAt(const QModelIndex &index) const;

    /**
     * Returns the terrain at the given \a index, or 0 if there is no terrain.
     */
    Terrain *terrainAt(const QModelIndex &index) const;

private slots:
    void tilesetAboutToBeAdded(int index);
    void tilesetAdded();
    void tilesetAboutToBeRemoved(int index);
    void tilesetRemoved();
    void tilesetChanged(Tileset *tileset);

    void terrainAboutToBeAdded(Tileset *tileset, int terrainId);
    void terrainAdded(Tileset *tileset);
    void terrainAboutToBeRemoved(Tileset *tileset, Terrain *terrain);
    void terrainRemoved(Tileset *tileset);

private:
    MapDocument *mMapDocument;
};

} // namespace Internal
} // namespace Tiled

#endif // TERRAINMODEL_H