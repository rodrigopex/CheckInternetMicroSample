/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2
import tc.utils 1.0

Page {
    Container {
        layout: DockLayout {
        }
        Container {
            attachedObjects: [
                ConnectionInfo {
                    id: connInfo
                }
            ]
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            Container {
                Label {
                    text: "Interface"
                    textStyle.base: SystemDefaults.TextStyles.BodyText
                    verticalAlignment: VerticalAlignment.Center
                }
            }
            Container {
                Label {
                    //id: interfaceLabel
                    text: connInfo.interfaceName
                    textStyle.base: SystemDefaults.TextStyles.BigText
                    verticalAlignment: VerticalAlignment.Center
                }
            }
            Container {
                topMargin: 30
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    // Localized text with the dynamic translation and locale updates support
                    text: qsTr("Internet connection status") + Retranslate.onLocaleOrLanguageChanged
                    textStyle.base: SystemDefaults.TextStyles.SubtitleText
                    verticalAlignment: VerticalAlignment.Center
                }
                ImageView {
                    //id: led
                    imageSource: (connInfo.connected ? "asset:///green_on.png" : "asset:///red_on.png")
                    verticalAlignment: VerticalAlignment.Center
                }
            }
        }
    }
}
