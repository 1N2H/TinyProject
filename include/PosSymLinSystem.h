#ifndef POS_SYM_LIN_SYSTEM_H
#define POS_SYM_LIN_SYSTEM_H

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    virtual ~PosSymLinSystem();
    
    virtual Vector Solve() const override;
};

#endif // POS_SYM_LIN_SYSTEM_H