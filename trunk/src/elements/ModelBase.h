#ifndef MODELBASE_H
#define MODELBASE_H


class ModelBase{
  public:
    virtual ~ModelBase();
    virtual void draw()=0;
  protected:
};

#endif // MODELBASE_H
