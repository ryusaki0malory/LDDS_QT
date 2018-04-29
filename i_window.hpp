#ifndef I_WINDOW_HPP
#define I_WINDOW_HPP


class I_window
{
public:
    virtual ~I_window();
    virtual void setLayoutWindow(QWidget *view);
};

#endif // I_WINDOW_HPP
