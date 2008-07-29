/***************************************************************************
 *   Copyright (C) 2007 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef CUSTOMTRACKVIEW_H
#define CUSTOMTRACKVIEW_H

#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QMenu>

#include <KUndoStack>

#include "kdenlivedoc.h"
#include "docclipbase.h"
#include "guide.h"
#include "effectslist.h"

class ClipItem;
class AbstractClipItem;
class Transition;

class CustomTrackView : public QGraphicsView {
    Q_OBJECT

public:
    CustomTrackView(KdenliveDoc *doc, QGraphicsScene * projectscene, QWidget *parent = 0);
    virtual ~ CustomTrackView();
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    void addTrack(TrackInfo type);
    void removeTrack();
    int cursorPos();
    void checkAutoScroll();
    void moveClip(const ItemInfo start, const ItemInfo end);
    /** move transition, startPos = (old start, old end), endPos = (new start, new end) */
    void moveTransition(const ItemInfo start, const ItemInfo end);
    void resizeClip(const ItemInfo start, const ItemInfo end);
    void addClip(QDomElement xml, int clipId, ItemInfo info, EffectsList list = EffectsList());
    void deleteClip(ItemInfo info);
    void slotAddClipMarker();
    void slotEditClipMarker();
    void slotDeleteClipMarker();
    void slotDeleteAllClipMarkers();
    void addMarker(const int id, const GenTime &pos, const QString comment);
    void setScale(double scaleFactor);
    void deleteClip(int clipId);
    void slotAddEffect(QDomElement effect, GenTime pos, int track);
    void addEffect(int track, GenTime pos, QDomElement effect);
    void deleteEffect(int track, GenTime pos, QDomElement effect);
    void updateEffect(int track, GenTime pos, QDomElement effect, int ix);
    void moveEffect(int track, GenTime pos, int oldPos, int newPos);
    void addTransition(ItemInfo transitionInfo, int endTrack, QDomElement params);
    void deleteTransition(ItemInfo transitionInfo, int endTrack, QDomElement params);
    void updateTransition(int track, GenTime pos,  QDomElement oldTransition, QDomElement transition);
    void moveTransition(GenTime oldpos, GenTime newpos);
    void activateMonitor();
    int duration() const;
    void deleteSelectedClips();
    void cutSelectedClips();
    void setContextMenu(QMenu *timeline, QMenu *clip, QMenu *transition);
    void checkTrackHeight();
    QList <TrackInfo> tracksList() const;
    void setTool(PROJECTTOOL tool);
    void cutClip(ItemInfo info, GenTime cutTime, bool cut);
    void slotSeekToPreviousSnap();
    void slotSeekToNextSnap();
    double getSnapPointForPos(double pos);
    void editKeyFrame(const GenTime pos, const int track, const int index, const QString keyframes);
    bool findString(const QString &text);
    bool findNextString(const QString &text);
    void initSearchStrings();
    void clearSearchStrings();
    void clipStart();
    void clipEnd();
    void changeClipSpeed();
    void doChangeClipSpeed(ItemInfo info, double speed, int id);

public slots:
    void setCursorPos(int pos, bool seek = true);
    void moveCursorPos(int delta);
    void updateCursorPos();
    void slotDeleteEffect(ClipItem *clip, QDomElement effect);
    void slotChangeEffectState(ClipItem *clip, int effectPos, bool disable);
    void slotChangeEffectPosition(ClipItem *clip, int currentPos, int newPos);
    void slotUpdateClipEffect(ClipItem *clip, QDomElement oldeffect, QDomElement effect, int ix);
    void slotRefreshEffects(ClipItem *clip);
    void setDuration(int duration);
    void slotAddTransition(ClipItem* clip, ItemInfo transitionInfo, int endTrack, QDomElement transition = QDomElement());
    void slotAddTransitionToSelectedClips(QDomElement transition);
    void slotTransitionUpdated(Transition *, QDomElement);
    void slotSwitchTrackAudio(int ix);
    void slotSwitchTrackVideo(int ix);
    void slotUpdateClip(int clipId);
    void slotAddClipMarker(int id, GenTime t, QString c);
    bool addGuide(const GenTime pos, const QString &comment);
    void slotAddGuide();
    void slotEditGuide(CommentedTime guide);
    void slotEditGuide();
    void slotDeleteGuide();
    void slotDeleteAllGuides();
    void editGuide(const GenTime oldPos, const GenTime pos, const QString &comment);
    void copyClip();
    void pasteClip();
    void pasteClipEffects();

protected:
    virtual void drawBackground(QPainter * painter, const QRectF & rect);
    //virtual void drawForeground ( QPainter * painter, const QRectF & rect );
    virtual void dragEnterEvent(QDragEnterEvent * event);
    virtual void dragMoveEvent(QDragMoveEvent * event);
    virtual void dragLeaveEvent(QDragLeaveEvent * event);
    virtual void dropEvent(QDropEvent * event);
    virtual void wheelEvent(QWheelEvent * e);
    virtual QStringList mimeTypes() const;
    virtual Qt::DropActions supportedDropActions() const;
    virtual void resizeEvent(QResizeEvent * event);

private:
    uint m_tracksHeight;
    int m_projectDuration;
    int m_cursorPos;
    ClipItem *m_dropItem;
    KdenliveDoc *m_document;
    void addItem(DocClipBase *clip, QPoint pos);
    QGraphicsLineItem *m_cursorLine;
    ItemInfo m_dragItemInfo;
    OPERATIONTYPE m_operationMode;
    OPERATIONTYPE m_moveOpMode;
    AbstractClipItem *m_dragItem;
    Guide *m_dragGuide;
    KUndoStack *m_commandStack;
    QGraphicsItem *m_visualTip;
    QGraphicsItemAnimation *m_animation;
    QTimeLine *m_animationTimer;
    QColor m_tipColor;
    QPen m_tipPen;
    double m_scale;
    QPoint m_clickPoint;
    QPoint m_clickEvent;
    QList <GenTime> m_snapPoints;
    QList <CommentedTime> m_searchPoints;
    QList <Guide *> m_guides;
    void updateSnapPoints(AbstractClipItem *selected);
    ClipItem *getClipItemAt(int pos, int track);
    ClipItem *getClipItemAt(GenTime pos, int track);
    Transition *getTransitionItemAt(int pos, int track);
    Transition *getTransitionItemAt(GenTime pos, int track);
    void checkScrolling();
    /** Should we auto scroll while playing (keep in sync with KdenliveSettings::autoscroll() */
    bool m_autoScroll;
    void displayContextMenu(QPoint pos, AbstractClipItem *clip = NULL);
    QMenu *m_timelineContextMenu;
    QMenu *m_timelineContextClipMenu;
    QMenu *m_timelineContextTransitionMenu;
    QList <TrackInfo> m_tracksList;
    QList <CommentedTime> m_searchStrings;
    int m_findIndex;
    PROJECTTOOL m_tool;
    QCursor m_razorCursor;
    /** list containing items currently copied in the timeline */
    QList<AbstractClipItem *> m_copiedItems;
    QList<AbstractClipItem *> m_selectedClipList;
    /** Used to get the point in timeline where a context menu was opened */
    QPoint m_menuPosition;

    /** Get the index of the video track that is just below current track */
    int getPreviousVideoTrack(int track);
    void updateClipFade(ClipItem * item, bool updateFadeOut = false);
    bool canBePastedTo(ItemInfo info, int type) const;
    bool canBePasted(QList<AbstractClipItem *> items, GenTime offset, int trackOffset) const;
    bool canBeMoved(QList<AbstractClipItem *> items, GenTime offset, int trackOffset) const;

private slots:
    void slotRefreshGuides();

signals:
    void cursorMoved(int, int);
    void zoomIn();
    void zoomOut();
    void mousePosition(int);
    void clipItemSelected(ClipItem*);
    void transitionItemSelected(Transition*);
    void activateDocumentMonitor();
    void trackHeightChanged();
    void displayMessage(const QString, MessageType);
    void showClipFrame(DocClipBase *, const int);
};

#endif

