/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     LiuMingHang <liuminghang@uniontech.com>
 *
 * Maintainer: ZhangYong <ZhangYong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef VIEWPANEL_H
#define VIEWPANEL_H

#include <QFrame>

#include <DStackedWidget>
#include <DAnchors>
#include <DIconButton>

#include <bitset>

#include "scen/imagegraphicsview.h"

class AbstractTopToolbar;

DWIDGET_USE_NAMESPACE
class LibImageInfoWidget;
class ExtensionPanel;
class NavigationWidget;
class LibBottomToolbar;
class LibTopToolbar;
class OcrInterface;
class LibSlideShowPanel;
class QPropertyAnimation;
class LockWidget;
class ThumbnailWidget;

class LibViewPanel : public QFrame
{

    Q_OBJECT
public:
    explicit LibViewPanel(AbstractTopToolbar *customToolbar = nullptr, QWidget *parent = nullptr);
    ~LibViewPanel() override;

    void loadImage(const QString &path, QStringList paths);

    void initConnect();
    //初始化标题栏
    void initTopBar();
    //初始化ocr
    void initOcr();
    //初始化缩放比和导航窗口
    void initFloatingComponent();
    //初始化缩放比例的窗口
    void initScaleLabel();
    //初始化导航窗口
    void initNavigation();
    //初始化右键菜单
    void initRightMenu();
    //初始化详细信息
    void initExtensionPanel();
    //幻灯片初始化
    void initSlidePanel();
    //损坏图片初始化
    void initLockPanel();
    //删除图片初始化
    void initThumbnailWidget();
    //初始化快捷键
    void initShortcut();
    //更新右键菜单
    void updateMenuContent(QString path = "");
    //控制全屏和返回全屏
    void toggleFullScreen();
    //全屏
    void showFullScreen();
    //退出全屏
    void showNormal();
    /**
     * @brief appendAction  添加右键菜单按钮
     * @param id            按钮枚举ID
     * @param text          按钮名称
     * @param shortcut      按钮快捷键
     */
    void appendAction(int id, const QString &text, const QString &shortcut = "");

    //设置壁纸
    void setWallpaper(const QImage &img);

    //drag事件打开图片
    bool startdragImage(const QStringList &paths, const QString &firstPath = "");

    //设置topBar的显示和隐藏
    void setTopBarVisible(bool visible);

    //设置Bottomtoolbar的显示和隐藏
    void setBottomtoolbarVisible(bool visible);

    //设置右键菜单显隐：false为永久隐藏，true为跟随原有策略显示或隐藏
    void setContextMenuItemVisible(imageViewerSpace::NormalMenuItemId id, bool visible);

    //设置下方工具栏按钮的显示和隐藏，false为永久隐藏，true为跟随原有策略显示或隐藏
    void setBottomToolBarButtonAlawysNotVisible(imageViewerSpace::ButtonType id, bool notVisible);

    //获得工具栏按钮
    DIconButton *getBottomtoolbarButton(imageViewerSpace::ButtonType type);

    //获得当前展示图片路径
    QString getCurrentPath();
private slots:
    void onMenuItemClicked(QAction *action);

    //存在图片刷新
    void slotOneImgReady(QString path, imageViewerSpace::ItemInfo itemInfo);
public slots:
    //刷新底部工具栏大小与位置
    void resetBottomToolbarGeometry(bool visible);
    //打开图片
    void openImg(int index, QString path);

    //旋转图片
    void slotRotateImage(int angle);

    //适应窗口和图片
    void slotResetTransform(bool bRet);

    //ocr连接
    bool slotOcrPicture();

    //回到视图界面
    void backImageView(const QString &path = "");

    //选择打开窗口
    bool startChooseFileDialog();

    //刷新底部工具栏在全屏的隐藏与否
    void slotBottomMove();

    //下一张图片
    void showNext();

    //上一张图片
    void showPrevious();

protected:
    void resizeEvent(QResizeEvent *e) override;
    void showEvent(QShowEvent *e) override;
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
signals:
    void imageChanged(const QString &path);

    //刷新缩略图
    void updateThumbnail(QPixmap pix, const QSize &originalSize);
private :
    DStackedWidget *m_stack = nullptr;
    LibImageGraphicsView *m_view = nullptr;
    LockWidget *m_lockWidget = nullptr;
    ThumbnailWidget *m_thumbnailWidget = nullptr;
    LibBottomToolbar *m_bottomToolbar = nullptr;
    LibImageInfoWidget *m_info = nullptr;
    ExtensionPanel  *m_extensionPanel {nullptr};
    DAnchors<NavigationWidget> m_nav ;

    //ocr接口
    OcrInterface *m_ocrInterface{nullptr};

    AbstractTopToolbar *m_topToolbar = nullptr;
    bool m_topToolBarIsAlwaysHide = false;

    DMenu *m_menu = nullptr;
    std::bitset<imageViewerSpace::MenuItemCount> m_menuItemDisplaySwitch;

    bool m_isMaximized = false;

    QTimer *m_tSaveImage = nullptr;//保存旋转图片定时器

    LibSlideShowPanel *m_sliderPanel{nullptr};

    QPropertyAnimation *m_bottomAnimation{nullptr};

    bool m_isBottomBarVisble = true;

    QString m_currentPath = "";
};
#endif  // VIEWPANEL_H
