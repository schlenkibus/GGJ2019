#include "TenantView.h"
#include "../Application.h"


TenantView::TenantView(TenantData& ref) : YesNoMessage([]() {Application::get().getLevel().pushMessage("Happy Animal");},
        [&]() {Application::get().getLevel().pushMessage(ref.getOutcome());},
        ref.toString()) {

}

