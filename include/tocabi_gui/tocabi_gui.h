#ifndef tocabi_gui__TocabiGUI_H
#define tocabi_gui__TocabiGUI_H

#include <rqt_gui_cpp/plugin.h>
#include <tocabi_gui/ui_tocabi_gui.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <ros/macros.h>

#include <QList>
#include <QString>
#include <QSize>
#include <QWidget>
#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QEventTransition>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <geometry_msgs/PolygonStamped.h>
#include <std_msgs/String.h>
#include <QMetaType>

#include <QGraphicsRectItem>
#include <QGraphicsSceneWheelEvent>

#include <QStringListModel>

#include "tocabi_controller/TaskCommand.h"
#include "tocabi_controller/TaskCommandQue.h"

const double NM2CNT[33] =
    {       //Elmo 순서
        95, //head
        95,
        95, //wrist
        95,
        95,
        95,
        15.5, //shoulder3
        15.5, //arm
        15.5, //arm
        15.5, //shoulder3
        42,   //Elbow
        42,   //Forearm
        42,   //Forearm
        42,   //Elbow
        15.5, //shoulder1
        15.5, //shoulder2
        15.5, //shoulder2
        15.5, //shoulder1
        3.3,  //Waist
        3.3,
        5.8, //rightLeg
        4.3,
        3.8,
        3.46,
        3.52,
        12.33,
        3.3, //upperbody
        5.8, //leftLeg
        4.3,
        3.8,
        3.46,
        3.52,
        12.33};

struct task_que
{
    std::string task_title;
    tocabi_controller::TaskCommand tc_;
};

namespace tocabi_gui
{

class MyQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyQGraphicsScene(QWidget *parent = 0);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:

private:
};

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    //virtual void wheelEvent(QGraphicsViewWheelEvent *event);
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

public slots:

private:
};

class TocabiGui : public rqt_gui_cpp::Plugin
{
    Q_OBJECT
public:
    TocabiGui();

    virtual void initPlugin(qt_gui_cpp::PluginContext &context);
    virtual void shutdownPlugin();
    virtual void saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const;
    virtual void restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings);

protected slots:
    //virtual void updateTopicList();
    virtual void torqueoncb();
    virtual void torqueoffcb();
    virtual void emergencyoffcb();
    //virtual void logbtn();
    virtual void plainTextEditcb(const std_msgs::StringConstPtr &msg);
    virtual void ecatpbtn();
    virtual void statpbtn();
    virtual void commandpbtn();
    virtual void initializebtncb();
    virtual void safetyresetbtncb();
    virtual void mtunebtn();
    virtual void walkinginitbtncb();
    virtual void walkingstartbtncb();
    virtual void walkingbtn();
    virtual void sendtunebtn();
    virtual void resettunebtn();
    virtual void pointcb(const geometry_msgs::PolygonStampedConstPtr &msg);
    virtual void imucb(const sensor_msgs::ImuConstPtr &msg);
    virtual void timercb(const std_msgs::Float32ConstPtr &msg);
    virtual void ftcalibbtn();
    virtual void tasksendcb();
    virtual void stateestimationcb();
    virtual void torquerediscb();
    virtual void qp2ndcb();
    virtual void customtaskgaincb(int state);
    virtual void fixedgravcb();
    virtual void gravcompcb();
    virtual void posconcb();
    virtual void posgravconcb();
    virtual void dshowbtn();
    virtual void ecatinitlow();
    virtual void safety2btncb();
    virtual void que_downbtn();
    virtual void que_upbtn();
    virtual void que_deletebtn();
    virtual void que_resetbtn();
    virtual void que_sendbtn();
    virtual void que_addquebtn();
    virtual void shutdown_robot();
    virtual void sysstatecb(const std_msgs::Int32MultiArrayConstPtr &msg);
    virtual void solvermode_cb(int state);
    virtual void inityaw();
    virtual void simvj();
    virtual void imureset();
    virtual void walkingspeedcb(int value);
    virtual void walkingdurationcb(int value);
    virtual void walkingangvelcb(int value);
    virtual void kneetargetanglecb(int value);
    virtual void footheightcb(int value);

    void handletaskmsg();

private:
    //ROS_DEPRECATED virtual QList<QString>
    std::vector<task_que> tq_;

    Ui::TocabiGuiWidget ui_;
    QWidget *widget_;

    //QStringListModel *model;
    //QStringList list;

    std::vector<QLabel *> ecatlabels;
    std::vector<QLabel *> safetylabels;
    std::vector<QLineEdit *> ecattexts;
    MyQGraphicsScene *scene;
    MyQGraphicsView *view;

    QGraphicsEllipseItem *com_d;
    QGraphicsRectItem *rfoot_d;
    QGraphicsLineItem *rfoot_l1;
    QGraphicsLineItem *rfoot_l2;
    QGraphicsRectItem *lfoot_d;
    QGraphicsLineItem *lfoot_l1;
    QGraphicsLineItem *lfoot_l2;
    QGraphicsRectItem *Pelv;
    QGraphicsEllipseItem *zmp;

    QGraphicsEllipseItem *rfoot_c;
    QGraphicsEllipseItem *lfoot_c;

    double robot_time;

    ros::NodeHandle nh_;

public:
    ros::Subscriber timesub;
    ros::Subscriber jointsub;
    ros::Subscriber pointsub;

    ros::Subscriber guilogsub;
    ros::Publisher gain_pub;
    std_msgs::Float32MultiArray gain_msg;
    ros::Publisher com_pub;
    std_msgs::String com_msg;

    ros::Publisher task_pub;
    tocabi_controller::TaskCommand task_msg;

    ros::Publisher task_que_pub;
    tocabi_controller::TaskCommandQue task_que_msg;

    ros::Publisher walkingspeed_pub;
    std_msgs::Float32 walkingspeed_msg;
    ros::Publisher walkingduration_pub;
    std_msgs::Float32 walkingduration_msg;
    ros::Publisher walkingangvel_pub;
    std_msgs::Float32 walkingangvel_msg;
    ros::Publisher kneetargetangle_pub;
    std_msgs::Float32 kneetargetangle_msg;
    ros::Publisher footheight_pub;
    std_msgs::Float32 footheight_msg;

    ros::Subscriber sysstatesub;

    ros::Subscriber imusub;

    //void guiLogCallback(const std_msgs::StringConstPtr &msg);
    std::string logtext;

signals:
    void guiLogCallback(const std_msgs::StringConstPtr &msg);
    void pointCallback(const geometry_msgs::PolygonStampedConstPtr &msg);
    void timerCallback(const std_msgs::Float32ConstPtr &msg);
    void imuCallback(const sensor_msgs::ImuConstPtr &msg);
    void sysstateCallback(const std_msgs::Int32MultiArrayConstPtr &msg);
    virtual void guiLogSignal();
};

} // namespace tocabi_gui
Q_DECLARE_METATYPE(std_msgs::StringConstPtr);
Q_DECLARE_METATYPE(geometry_msgs::PolygonStampedConstPtr);
Q_DECLARE_METATYPE(std_msgs::Float32ConstPtr);
Q_DECLARE_METATYPE(sensor_msgs::ImuConstPtr);
Q_DECLARE_METATYPE(std_msgs::Int32MultiArrayConstPtr);

#endif
