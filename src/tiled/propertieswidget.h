/*
 * propertieswidget.h
 * Copyright 2013-2023, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#pragma once

#include <QMap>
#include <QPointer>
#include <QWidget>

class QScrollArea;

namespace Tiled {

class Object;

class AddValueProperty;
class CustomProperties;
class Document;
class GroupProperty;
class ObjectProperties;
class VariantEditorView;

/**
 * The PropertiesWidget combines the PropertyBrowser with some controls that
 * allow adding and removing properties. It also implements cut, copy and paste
 * actions and the context menu.
 */
class PropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropertiesWidget(QWidget *parent = nullptr);
    ~PropertiesWidget() override;

    /**
     * Sets the \a document on which this properties dock will act.
     */
    void setDocument(Document *document);

    GroupProperty *customPropertiesGroup() const;
    VariantEditorView *propertiesView() const { return mPropertyBrowser; }

signals:
    void bringToFront();

public slots:
    void selectCustomProperty(const QString &name);

protected:
    bool event(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void currentObjectChanged(Object *object);
    void updateActions();

    void cutProperties();
    bool copyProperties();
    void pasteProperties();
    void showAddValueProperty();
    void addProperty(const QString &name, const QVariant &value);
    void removeProperties();
    void renameProperty(const QString &name);
    void showContextMenu(const QPoint &pos);

    void retranslateUi();

    Document *mDocument = nullptr;
    ObjectProperties *mPropertiesObject = nullptr;
    CustomProperties *mCustomProperties = nullptr;
    QPointer<AddValueProperty> mAddValueProperty;
    QMap<int, bool> mExpandedStates;
    VariantEditorView *mPropertyBrowser;
    QAction *mActionAddProperty;
    QAction *mActionRemoveProperty;
    QAction *mActionRenameProperty;
};

} // namespace Tiled
